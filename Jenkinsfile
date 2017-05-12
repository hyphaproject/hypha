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

        stage('Build Coverage') {
            steps {
                echo 'Building Coverage ...'
                sh 'mkdir -p build_coverage && cd build_coverage && cmake -DOPTION_BUILD_TESTS=1 -DCMAKE_BUILD_TYPE=Coverage ..'
                sh 'cmake --build build_coverage --target hyphacore-test_coverage'
                publishHTML([allowMissing: false, alwaysLinkToLastBuild: false, keepAll: false, reportDir: 'build_coverage/coverage', reportFiles: 'index.html', reportName: 'Coverage', reportTitles: ''])
            }
        }
    }
}