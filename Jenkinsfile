@Library("shared-jenkins-pipelines@codex/add-pipeline-for-arduino-.ino-compilation") _

pipeline {
    agent any
    when { anyOf { buildingBranch(); branch 'main'; branch 'master' } }
    stages {
        stage('Build') {
            steps {
                platformioPipeline('publishOffbeat':'false', 'arduinoFqbn':'esp8266:esp8266:generic')
            }
        }
    }
}
