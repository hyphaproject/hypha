pipeline {

    stages {
        stage('Build') {
            steps {
                echo 'Building ...'
                sh 'mkdir -p build && cd build'
                sh 'cmake ..'
                sh 'cmake --build .'
            }
        }

        stage('Build Docs') {
            steps {
                echo 'Building Docs ...'
                sh 'mkdir -p build_docs && cd build_docs'
                sh 'cmake -DOPTION_BUILD_DOCS=1 ..'
                sh 'cmake --build . --target docs'
            }
        }
    }
}