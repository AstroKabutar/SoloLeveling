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
  region     = var.aws_regions["india"]
  access_key = "AKIAQ3EGQDDBHORHGKFH"
  secret_key = "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"
}

# ---------------------------- VPC peering resource ------------------------------------------------------------------

##resource "aws_vpc_peering_connection" "peer" {
##  vpc_id      = aws_vpc.my-first-vpc-via-terraform.id
##  peer_vpc_id = aws_vpc.vpc-peering.id
##  auto_accept = true
##}
##
### ---------------------------------- 2ND VPC CREATION FOR THE VPC PEERING ---------------------------------
##
### --------------------- VPC creation ------------------
### VPC creation
##resource "aws_vpc" "vpc-peering" {
##  cidr_block = var.vpc_cidr_individual["cidr1"]
##
##  tags = {
##    Name = "${var.environment}-vpc-peering"
##    Environment = var.environment
##  }
##}
##
### --------------------------Subnets creation-------------------
### vpc-peering peer
##resource "aws_subnet" "publicApeer" {
##  vpc_id                  = aws_vpc.vpc-peering.id
##  cidr_block              = var.vpc_cidr_subnet["peerpublicA"]
##  availability_zone       = local.aws_az["indiaAZ3"]
##
##  # this automatically maps public ip to ec2 instances launched
##  map_public_ip_on_launch = true
##
##  tags = {
##    Name = "Public subnet A peer"
##  }
##}
##
### Route table creation and explicit associations for both private and public
### Route tables for routing traffic for public subnets
##resource "aws_route_table" "PublicRouteTablepeer" {
##  vpc_id = aws_vpc.vpc-peering.id
##
##  route {
##    cidr_block                = var.vpc_cidr_individual["cidr0"]
##    vpc_peering_connection_id = aws_vpc_peering_connection.peer.id
##  }
##  
##  route {
##    cidr_block = "0.0.0.0/0"
##    gateway_id = aws_internet_gateway.IGWpeer.id
##  }
##
##  tags = {
##    Name = "Route Table for main vpc to peer"
##  }
##}
##
### Route table explicit associations for both Public subnet
##resource "aws_route_table_association" "publicApeerassociation" {
##  subnet_id      = aws_subnet.publicApeer.id
##  route_table_id = aws_route_table.PublicRouteTablepeer.id
##}
##
### ----------------------------Internet Gateway creation------------------------
##resource "aws_internet_gateway" "IGWpeer" {
##  vpc_id = aws_vpc.vpc-peering.id
##  tags = {
##    Name = "Shahin VPC peer"
##  }
##}
##
### ------------------------------Elastic-IP (eip) for NAT-----------------------
##resource "aws_eip" "nat_eip_peer" {
##  domain = "vpc"
##
##  tags = {
##    Name = "NAT IP peer"
##  }
##}
##
### ----------------------------------NAt gateway creation-------------------------
##resource "aws_nat_gateway" "NATpeer" {
##  subnet_id        = aws_subnet.publicA.id
##  allocation_id    = aws_eip.nat_eip_peer.id
##
##  tags = {
##    Name = "NAT Gateway peer"
##  }
##
##  # To ensure proper ordering, it is recommended to add an explicit dependency
##  # on the Internet Gateway for the VPC.
##  depends_on = [aws_internet_gateway.IGWpeer, aws_eip.nat_eip_peer]
##}
##
### ---------------------------------- 2ND VPC CREATION FOR THE VPC PEERING ENDS ----------------------------------
##
##
### ----------------------------- 2nd vpc instance creation for test ---------------------
##
### create a security group
##resource "aws_security_group" "peerhost" {
##  name        = "peerhost"
##  description = "Allow tcp inbound traffic"
##  vpc_id      = aws_vpc.vpc-peering.id
##
##  tags = {
##    Name = "peerhost"
##  }
##}
##
### ingress rule for tcp to port 80 from anywhere in the world for ssh
##resource "aws_vpc_security_group_ingress_rule" "allow_tcp_80_ipv4_public_peer" {
##  security_group_id = aws_security_group.peerhost.id
##  cidr_ipv4         = "0.0.0.0/0"
##  from_port         = 80
##  ip_protocol       = "tcp"
##  to_port           = 80
##}
##
### ingress rule for tcp to port 22 from anywhere in the world for ssh
##resource "aws_vpc_security_group_ingress_rule" "allow_tcp_22_ipv4_public_peer" {
##  security_group_id = aws_security_group.peerhost.id
##  cidr_ipv4         = "0.0.0.0/0"
##  from_port         = 22
##  ip_protocol       = "tcp"
##  to_port           = 22
##}
##
### an eggress rule to allow tcp from vm to the www
##resource "aws_vpc_security_group_egress_rule" "allow_all_traffic_ipv4_public_peer" {
##  security_group_id = aws_security_group.peerhost.id
##  cidr_ipv4         = "0.0.0.0/0"
##  ip_protocol       = "-1" # semantically equivalent to all ports
##}
##
### EC2 BastionHostEC
##resource "aws_instance" "peerhost" {
##  ami                     = "ami-0131b8f4c937c332f"           # debian arm64 ami
##  instance_type           = "t4g.nano"
##  vpc_security_group_ids  = [aws_security_group.peerhost.id]
##
##  subnet_id               = aws_subnet.publicApeer.id
##
##  key_name = module.key_pair.key_pair_name
##
##  tags = {
##    Name = "peerhost Host"
##  }
##}
### ----------------------------- 2nd vpc instance creation for test ends -----------------------------------------------
### ---------------------------- VPC peering resource ends ---------------------------------------------------------------------------

# ---------------------VPC creation------------------
# VPC creation
resource "aws_vpc" "my-first-vpc-via-terraform" {
  cidr_block = var.vpc_cidr_individual["cidr0"]

  tags = {
    Name = "${var.environment}-vpc"
    Environment = var.environment
  }
}

# --------------------------Subnets creation-------------------
# publicA
resource "aws_subnet" "publicA" {
  vpc_id                  = aws_vpc.my-first-vpc-via-terraform.id
  cidr_block              = var.vpc_cidr_subnet["publicA"]
  availability_zone       = local.aws_az["indiaAZ1"]

  # this automatically maps public ip to ec2 instances launched
  map_public_ip_on_launch = true

  tags = {
    Name = "Public subnet A"
  }
}

# publicB
resource "aws_subnet" "publicB" {
  vpc_id                  = aws_vpc.my-first-vpc-via-terraform.id
  cidr_block              = var.vpc_cidr_subnet["publicB"]
  availability_zone       = local.aws_az["indiaAZ2"]

  # this automatically maps public ip to ec2 instances launched
  map_public_ip_on_launch = true

  tags = {
    Name = "Public subnet B"
  }
}

# privateA
resource "aws_subnet" "privateA" {
  vpc_id            = aws_vpc.my-first-vpc-via-terraform.id
  cidr_block        = var.vpc_cidr_subnet["privateA"]
  availability_zone = local.aws_az["indiaAZ1"]

  tags = {
    Name = "Private subnet A"
  }
}

# privateB
resource "aws_subnet" "privateB" {
  vpc_id            = aws_vpc.my-first-vpc-via-terraform.id
  cidr_block        = var.vpc_cidr_subnet["privateB"]
  availability_zone = local.aws_az["indiaAZ2"]

  tags = {
    Name = "Private subnet B"
  }
}

# ----------------------------Internet Gateway creation------------------------
resource "aws_internet_gateway" "IGW" {
  vpc_id = aws_vpc.my-first-vpc-via-terraform.id
  tags = {
    Name = "Shahin VPC"
  }
}

# ------------------------------Elastic-IP (eip) for NAT-----------------------
resource "aws_eip" "nat_eip" {
  domain = "vpc"

  tags = {
    Name = "NAT IP"
  }
}

# ----------------------------------NAt gateway creation-------------------------
resource "aws_nat_gateway" "NAT" {
  subnet_id        = aws_subnet.publicA.id
  allocation_id    = aws_eip.nat_eip.id

  tags = {
    Name = "NAT Gateway"
  }

  # To ensure proper ordering, it is recommended to add an explicit dependency
  # on the Internet Gateway for the VPC.
  depends_on = [aws_internet_gateway.IGW, aws_eip.nat_eip]
}

# Route table creation and explicit associations for both private and public
# Route tables for routing traffic for public subnets
resource "aws_route_table" "PublicRouteTable" {
  vpc_id = aws_vpc.my-first-vpc-via-terraform.id

  route {
    cidr_block = "0.0.0.0/0"
    gateway_id = aws_internet_gateway.IGW.id
  }

### ----------------------------------------------------Route table for 2vpc peering ----------------<><><><><>>>-----------------------------
##  route {
##    cidr_block = var.vpc_cidr_individual["cidr1"]
##    vpc_peering_connection_id = aws_vpc_peering_connection.peer.id
##  }
### -------------------------------------------------------------------------------------------------------------------------------------------

  tags = {
    Name = "Route Table for public subnet"
  }
}

# Route table explicit associations for both Public subnet
resource "aws_route_table_association" "publicA" {
  subnet_id      = aws_subnet.publicA.id
  route_table_id = aws_route_table.PublicRouteTable.id
}
resource "aws_route_table_association" "publicB" {
  subnet_id      = aws_subnet.publicB.id
  route_table_id = aws_route_table.PublicRouteTable.id
}


# Route tables for routing traffic for private subnets
resource "aws_route_table" "PrivateRouteTable" {
  vpc_id = aws_vpc.my-first-vpc-via-terraform.id

  route {
    cidr_block = "0.0.0.0/0"
    nat_gateway_id = aws_nat_gateway.NAT.id
  }

  tags = {
    Name = "Route Table for private subnet"
  }
}

# Route table explicit associations for both Private subnet
resource "aws_route_table_association" "privateA" {
  subnet_id      = aws_subnet.privateA.id
  route_table_id = aws_route_table.PrivateRouteTable.id
}
resource "aws_route_table_association" "privateB" {
  subnet_id      = aws_subnet.privateB.id
  route_table_id = aws_route_table.PrivateRouteTable.id
}



# ----------------------------key pair-----------------------------------
# https://github.com/terraform-aws-modules/terraform-aws-key-pair
module "key_pair" {
  source             = "terraform-aws-modules/key-pair/aws"
  key_name           = "BastionHost"
  create_private_key = true
}

# store 
resource "local_file" "private_key_pem" {
  content  = module.key_pair.private_key_pem
  filename = "${path.module}/BastionHost.pem"
  file_permission = "0600"
}
# -----------------------------------------------------------------------

# ----------------------------NACL SETTINGS------------------------------

#resource "aws_network_acl" "vpc-nacl" {
#  vpc_id = aws_vpc.my-first-vpc-via-terraform.id
#
#  tags = {
#    Name = "Custom NACL"
#  }
#}
#
## NACL subnet associations only publicA/B for playing around
#resource "aws_network_acl_association" "publicA" {
#  network_acl_id = aws_network_acl.vpc-nacl.id
#  subnet_id = aws_subnet.publicA.id
#}
#resource "aws_network_acl_association" "publicB" {
#  network_acl_id = aws_network_acl.vpc-nacl.id
#  subnet_id = aws_subnet.publicB.id
#}
#
## incoming rule playground
#resource "aws_network_acl_rule" "vpc-nacl-in-tcp-http" {
#  network_acl_id = aws_network_acl.vpc-nacl.id
#  protocol = "tcp"
#  rule_number = 100
#  egress = false
#  rule_action = "allow"
#
#  from_port = 80
#  to_port = 80
#
#  # bastion host connectivity from anywhere
#  cidr_block = "0.0.0.0/0"
#}
#resource "aws_network_acl_rule" "vpc-nacl-in-tcp-ssh" {
#  network_acl_id = aws_network_acl.vpc-nacl.id
#  protocol = "tcp"
#  rule_number = 200
#  egress = false
#  rule_action = "allow"
#
#  from_port = 22
#  to_port = 22
#
#  # bastion host connectivity from anywhere
#  cidr_block = "0.0.0.0/0"
#}
#
## outgoing rule playground
#resource "aws_network_acl_rule" "vpc-nacl-out-tcp" {
#  network_acl_id = aws_network_acl.vpc-nacl.id
#  protocol = "tcp"
#  rule_number = 100
#  egress = true
#  rule_action = "allow"
#
#  # ephermal ports to let the server reply back to the client
#  from_port = 1024
#  to_port = 65535
#
#  # bastion host connectivity from anywhere
#  cidr_block = "0.0.0.0/0"
#}

# --------------------------NACL ENDS------------------------------------


# ----------------------------BASTION HOSTS SETTINGS--------------------------------
# create a security group
resource "aws_security_group" "BastionHostSG" {
  name        = "BastionHostSG"
  description = "Allow tcp inbound traffic"
  vpc_id      = aws_vpc.my-first-vpc-via-terraform.id

  tags = {
    Name = "BastionHostSG"
  }
}

# ingress rule for tcp to port 22 from anywhere in the world for ssh
resource "aws_vpc_security_group_ingress_rule" "allow_tcp_22_ipv4_public" {
  security_group_id = aws_security_group.BastionHostSG.id
  cidr_ipv4         = "0.0.0.0/0"
  from_port         = 22
  ip_protocol       = "tcp"
  to_port           = 22
}

# ingress rule for tcp to port 80 from anywhere in the world for ssh
resource "aws_vpc_security_group_ingress_rule" "allow_tcp_80_ipv4_public" {
  security_group_id = aws_security_group.BastionHostSG.id
  cidr_ipv4         = "0.0.0.0/0"
  from_port         = 80
  ip_protocol       = "tcp"
  to_port           = 80
}

# an eggress rule to allow tcp from vm to the www
resource "aws_vpc_security_group_egress_rule" "allow_all_traffic_ipv4_public" {
  security_group_id = aws_security_group.BastionHostSG.id
  cidr_ipv4         = "0.0.0.0/0"
  ip_protocol       = "-1" # semantically equivalent to all ports
}

# EC2 BastionHostEC
resource "aws_instance" "BastionHost" {
  ami                     = "ami-0131b8f4c937c332f"           # debian arm64 ami
  instance_type           = "t4g.nano"
  vpc_security_group_ids  = [aws_security_group.BastionHostSG.id]

  subnet_id               = aws_subnet.publicA.id

  key_name = module.key_pair.key_pair_name

  user_data =  base64encode(<<-EOF
               #!/bin/bash
               sudo apt-get update
               sudo apt install nginx -y
               sudo systemctl enable nginx
             
               sudo echo "Hello World from Bastion Host" > /var/www/html/index.nginx-debian.html
             
               sudo systemctl restart nginx
             
               EOF
  )

  tags = {
    Name = "Bastion Host"
  }
}
# --------------------------------------------------------------------------------------------------------

# -------------------------------PRIVATE INSTANCE SETTINGS------------------------------------------------

# create a security group
resource "aws_security_group" "PrivateSG" {
  name        = "PrivateSG"
  description = "Allow tcp inbound traffic from Bastion host"
  vpc_id      = aws_vpc.my-first-vpc-via-terraform.id

  tags = {
    Name = "PrivateSG"
  }
}

# ingress rule for tcp to port 22 from anywhere in the world for ssh
resource "aws_vpc_security_group_ingress_rule" "allow_tcp_22_ipv4_private" {
  security_group_id               = aws_security_group.PrivateSG.id
  #cidr_ipv4                       = var.vpc_cidr_subnet["publicA"]
  referenced_security_group_id    = aws_security_group.BastionHostSG.id
  from_port                       = 22
  ip_protocol                     = "tcp"
  to_port                         = 22

  description = "Allow TCP connections at 22 from PublicA subnet cider block"
}

# an eggress rule to allow tcp from vm to the www
resource "aws_vpc_security_group_egress_rule" "allow_all_traffic_ipv4_private" {
  security_group_id = aws_security_group.PrivateSG.id
  cidr_ipv4         = "0.0.0.0/0"
  ip_protocol       = "-1" # semantically equivalent to all ports
}

# EC2 PrivateEC
resource "aws_instance" "PrivateEC" {
  ami                     = "ami-0131b8f4c937c332f"           # debian arm64 ami
  instance_type           = "t4g.nano"
  vpc_security_group_ids  = [aws_security_group.PrivateSG.id]

  subnet_id               = aws_subnet.privateA.id

  key_name = module.key_pair.key_pair_name

  tags = {
    Name = "Private Instance"
  }
}

# --------------------------------------------------------------------------------------------------------