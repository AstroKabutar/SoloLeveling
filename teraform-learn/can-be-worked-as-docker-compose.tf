terraform {
  required_providers {
    docker = {
      source  = "kreuzwerker/docker"
      version = "~> 3.0.1"
    }
  }
}

provider "docker" {}

resource "docker_image" "portfoliodb" {
  name         = "schd1337/portfoliodb:v3"
  keep_locally = false
}

resource "docker_container" "tutorial" {
  name  = "tutorial"
  image = docker_image.portfoliodb.image_id

  ports {
    internal = 3306
    external = 8000
  }
}
