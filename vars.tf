# region variables
# turned it into array
# https://spacelift.io/blog/terraform-map-variable

variable "aws_regions" {
    type = map(string)
    default = {
        india = "ap-south-1"
    }
}

locals {
    aws_az = {
        indiaAZ1 = "${var.aws_regions["india"]}a"
        indiaAZ2 = "${var.aws_regions["india"]}b"
        indiaAZ3 = "${var.aws_regions["india"]}c"
    }
}

# CIDR array for vpc to be created for individual use
variable "vpc_cidr_individual" {
    type = map(string)
    default = {
        cidr1 = "10.1.0.0/16"
        cidr0 = "10.0.0.0/16"
    }

    description = "CIDR blocks of the vpc for individual use"
}

# CIDR array for subnet
variable "vpc_cidr_subnet" {
    type = map(string)
    default = {
        publicA     = "10.0.0.0/24"
        publicB     = "10.0.1.0/24"
        privateA    = "10.0.16.0/20"
        privateB    = "10.0.32.0/20"
        peerpublicA = "10.1.0.0/24"
    }
}


# environment
variable "environment" {
    default = "Shahin"
}