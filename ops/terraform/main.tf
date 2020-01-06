// PROVIDER

// provider "aws" {
//   region = "${var.aws_region}"
// }

// POSTGRES

// resource "aws_db_instance" "default" {
//   allocated_storage    = 20
//   storage_type         = "gp2"
//   engine               = "postgres"
//   engine_version       = "5.7"
//   instance_class       = "db.t2.micro"
//   name                 = "condorcet"
//   username             = "foo"
//   password             = "foobarbaz"
//   parameter_group_name = "default.mysql5.7"
// }


// ECS

// resource "aws_ecs_cluster" "main" {
//   name = "terraform_example_ecs_cluster"
// }

// ALB

// ROUTE53 to ALB
