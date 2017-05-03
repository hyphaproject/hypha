import subprocess

class pythonplugin:

    def __init__(self):
        #self.sendMessage = sendMessage
        text = '"init"'
        print(text+"\n\n")

    def name(self):
        return "pythonplugin"

    def getTitle(self):
        return "Python Plugin"

    def getVersion(self):
        return "0.1"

    def getDescription(self):
        return "Plugin running Python code"

    def doWork(self):
        text = '"doWork"'

    def setup(self):
        text = '"setup"'
        print(text+"\n\n")

    def communicate(self, message):
        return message;

    def loadConfig(self, json):
        text = json
        print(text+"\n\n")

    def getConfig(self):
        return "{}"

    def receiveMessage(self, message):
        print(message)
