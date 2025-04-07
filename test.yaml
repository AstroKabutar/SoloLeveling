pipeline {
    agent any
    stages {
        stage('Build') {
            steps {
                echo "Building project..."
                // Add your build steps here (e.g., running a shell command)
                echo $pwd
            }
        }
        stage('Test') {
            steps {
                echo "Running tests..."
                // Add your test steps here (e.g., running a test command)
                echo $USER
            }
        }
        stage('Deploy') {
            steps {
                echo "Deploying project..."
                // Add your deploy steps here (e.g., deploying to a server)
                echo $SHELL
            }
        }
    }
}
