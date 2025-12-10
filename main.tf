terraform {
  required_providers {
    aws = {
      source  = "hashicorp/aws"
      version = "~> 5.0"
    }
  }

  required_version = ">= 1.2.9"
}

# not recomended but best can be done via env variables or
# using python and os.getenv("VAR") both the same 
# more oppertunity for learn
provider "aws" {
  region = var.aws_regions["india"]
  access_key = "AKIAQ3EGQDDBCSYT6NRL"
  secret_key = "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"
}

# https://github.com/terraform-aws-modules/terraform-aws-key-pair
module "key_pair" {
  source             = "terraform-aws-modules/key-pair/aws"
  key_name           = "project-solo"
  create_private_key = true
}

# store 
resource "local_file" "private_key_pem" {
  content  = module.key_pair.private_key_pem
  filename = "${path.module}/project-solo.pem"
  file_permission = "0600"
}

# id would be aws_instance.my-first-terraform-ec2
resource "aws_instance" "my-first-terraform-ec2" {
  ami           = "ami-0131b8f4c937c332f"           # debian arm64 ami
  instance_type = "t4g.medium"
#  instance_type = "t4g.small"
  subnet_id               = aws_default_subnet.default.id
  vpc_security_group_ids = [aws_security_group.allow_tcp.id]

  key_name = module.key_pair.key_pair_name

  iam_instance_profile = "ec2_instance_profile"

  user_data = base64encode(<<-EOF
              #!/bin/bash
              apt-get update

              # install kubectl
              curl -LO "https://dl.k8s.io/release/$(curl -L -s https://dl.k8s.io/release/stable.txt)/bin/linux/arm64/kubectl"
              sudo install -o root -g root -m 0755 kubectl /usr/local/bin/kubectl

              # install minikube
              curl -LO https://github.com/kubernetes/minikube/releases/latest/download/minikube-linux-arm64
              sudo install minikube-linux-arm64 /usr/local/bin/minikube && rm minikube-linux-arm64

              # install docker
              sudo apt-get install ca-certificates curl
              sudo install -m 0755 -d /etc/apt/keyrings
              sudo curl -fsSL https://download.docker.com/linux/debian/gpg -o /etc/apt/keyrings/docker.asc
              sudo chmod a+r /etc/apt/keyrings/docker.asc

              # Add the repository to Apt sources:
              echo \
                "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.asc] https://download.docker.com/linux/debian \
                $(. /etc/os-release && echo "$VERSION_CODENAME") stable" | \
                sudo tee /etc/apt/sources.list.d/docker.list > /dev/null
              apt-get update

              # install docker
              sudo apt-get install docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin -y

              sudo apt install apache2 -y
              sudo systemctl enable apache2
              sudo systemctl start apache2

              alias k="kubectl"
              EOF
  )

  tags = {
    Name = "Portfolio EC2"
  }

# ebs root volume
  root_block_device {
    delete_on_termination = true
    volume_size = 30
    volume_type = "gp3"
  }
}


# going to use default vpc id
# The ID here becomes data.aws_vpc.default.id
data "aws_vpc" "default"{
  default = true
}

# default subnet az1 i choose for my ec2
resource "aws_default_subnet" "default" {
  availability_zone = local.aws_az["indiaAZ1"]
}


# create a security group with default vpc ID
resource "aws_security_group" "allow_tcp" {
  name = "allow_tcp"
  description = "Allow tcp inbound traffic"
  vpc_id = data.aws_vpc.default.id

  tags = {
    Name = "allow_tcp"
  }
}

# ingress rule for tcp to port 22 from anywhere in the world for ssh
resource "aws_vpc_security_group_ingress_rule" "allow_tcp_22_ipv4" {
  security_group_id = aws_security_group.allow_tcp.id
  cidr_ipv4         = "0.0.0.0/0"
  from_port         = 22
  ip_protocol       = "tcp"
  to_port           = 22
}

# ingress rule for tcp to port 80 from anywhere in the world for nginx httpd 80
resource "aws_vpc_security_group_ingress_rule" "allow_tcp_80_ipv4" {
  security_group_id = aws_security_group.allow_tcp.id
  cidr_ipv4         = "0.0.0.0/0"
  from_port         = 80
  ip_protocol       = "tcp"
  to_port           = 80
}

# an eggress rule to allow tcp from vm to the www
resource "aws_vpc_security_group_egress_rule" "allow_all_traffic_ipv4" {
  security_group_id = aws_security_group.allow_tcp.id
  cidr_ipv4         = "0.0.0.0/0"
  ip_protocol       = "-1" # semantically equivalent to all ports
}


# wireguard server server
# 5000/udp
resource "aws_vpc_security_group_ingress_rule" "allow_tcp_5000_ipv4" {
  security_group_id = aws_security_group.allow_tcp.id
  cidr_ipv4         = "0.0.0.0/0"
  from_port         = 5000
  ip_protocol       = "udp"
  to_port           = 5000
}

# ephermal ports/udp
resource "aws_vpc_security_group_ingress_rule" "allow_tcp_ephermal_ipv4" {
  security_group_id = aws_security_group.allow_tcp.id
  cidr_ipv4         = "0.0.0.0/0"
  from_port         = 32768
  ip_protocol       = "udp"
  to_port           = 61000
}
