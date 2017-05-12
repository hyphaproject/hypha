pipeline {
    agent any
    stages {
        stage('Build') {
            steps {
                echo 'Building ...'
                sh 'mkdir -p build && cd build && cmake ..'
                sh 'cmake --build build'
            }
        }

        stage('Build Docs') {
            steps {
                echo 'Building Docs ...'
                sh 'mkdir -p build_docs && cd build_docs && cmake -DOPTION_BUILD_DOCS=1 ..'
                sh 'cmake --build build_docs --target docs'
                publishHTML([allowMissing: false, alwaysLinkToLastBuild: false, keepAll: false, reportDir: 'build_docs/docs/api-docs/html', reportFiles: 'index.html', reportName: 'API DOCS', reportTitles: ''])
            }
        }
    }
}