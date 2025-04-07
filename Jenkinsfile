pipeline {
    agent any
    stages {
        stage('Build') {
            steps {
                echo "Building project..."
                // Correctly using pwd() function in Groovy
                echo "Current working directory: ${pwd()}"
            }
        }
        stage('Test') {
            steps {
                echo "Running tests..."
                // Accessing environment variables correctly in Groovy
                echo "User: ${env.USER}"    // Correct way to access environment variable
            }
        }
        stage('Deploy') {
            steps {
                echo "Deploying project..."
                // Accessing environment variable for the shell
                echo "Shell: ${env.SHELL}"
            }
        }
    }
}
