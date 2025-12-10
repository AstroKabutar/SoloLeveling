# https://awspolicygen.s3.amazonaws.com/policygen.html


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
  access_key = "AKIAQ3EGQDDBCSYT6NRL"
  secret_key = "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"
}

# ----------------------IAM ROLES & POLICIES ----------------

# AWS IAM role creation
data "aws_iam_policy_document" "assume_role" {
  statement {
    effect = "Allow"

    principals {
      type        = "Service"
      identifiers = ["ec2.amazonaws.com"]
    }

    actions = ["sts:AssumeRole"]
  }
}

# AWS IAM role creation completed
resource "aws_iam_role" "sns-trigger-ec2" {
  name               = "EC2snsPublish"
  assume_role_policy = data.aws_iam_policy_document.assume_role.json
}

# Policy creation in json
data "aws_iam_policy_document" "sns-publish-policy" {
  statement {
    effect = "Allow"
    actions = ["sns:Publish"]
    resources = [
          "arn:aws:sns:ap-south-1:058264131778:ec2-health-topic-email",
          "arn:aws:sns:ap-south-1:058264131778:ec2-health-topic-sms"
        ]
    }
}

# Policy creation getting in json
resource "aws_iam_policy" "sns-publish-policy" {
  name        = "sns-publish-policy"
  description = "SNS Publish only policy"
  policy      = data.aws_iam_policy_document.sns-publish-policy.json
}

# Attach the newly created policy to the newly created IAM role
resource "aws_iam_role_policy_attachment" "sns-policy-attach" {
  role       = aws_iam_role.sns-trigger-ec2.name
  policy_arn = aws_iam_policy.sns-publish-policy.arn
}

# Create an instance profile for the IAM role
resource "aws_iam_instance_profile" "sns-policy-attach" {
  name = "ec2_instance_profile"
  role = aws_iam_role.sns-trigger-ec2.name
}

# -----------------------------------------------------------

# SNS Topic creation and customization
resource "aws_sns_topic" "user_updates_email" {
  name = "ec2-health-topic-email"
  display_name = "EC2 Health topic email"
}

#resource "aws_sns_topic" "user_updates_sms" {
#  name = "ec2-health-topic-sms"
#  display_name = "EC2 Health topic sms"
#}

# Creating subscription
resource "aws_sns_topic_subscription" "user_update_email"{
    topic_arn = aws_sns_topic.user_updates_email.arn
    protocol = "email"
    endpoint = "xenxiao80@gmail.com"
}

#resource "aws_sns_topic_subscription" "user_update_sms"{
#    topic_arn = aws_sns_topic.user_updates_sms.arn
#    protocol = "sms"
#    endpoint = "+919748299749"
#}
