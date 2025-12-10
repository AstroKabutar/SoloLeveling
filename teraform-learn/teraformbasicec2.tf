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
  region = "ap-south-1"
  access_key = "AKIAQ3EGQDDBHORHGKFH"
  secret_key = "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"
}

resource "aws_instance" "my-first-terraform-ec2" {
  ami           = "ami-094ead6eb0a3fed45"
  instance_type = "t4g.nano"

  tags = {
    Name = "My first terraform created EC2"
  }
}
