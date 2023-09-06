from sourcemod import console
from sourcemod import files
from sourcemod import logging

logging.LogMessage('Hello from plugin1.py plugin!!!')

PYSMOD_PLUGIN = True

PLUGIN_INFO = {
    'name': '[L4D] Plugin 1',
    'author': 'samuelviveiros a.k.a Dartz8901',
    'description': 'Testing Python Plugin',
    'version': '0.1.0',
    'url': 'https://github.com/samuelviveiros/'
}

def OnPluginStart():
    try:
        console.PrintToConsole(1, "plugin1.py -> OnPluginStart: This is a print from Python! --")
    except:
        pass

    built_path = files.BuildPath(files.Path_SM, 'gamedata/foobar')
    logging.LogMessage(f'plugin1.py -> built_path: {built_path}')
    #logging.LogMessage(logging.BuildPath.__doc__)
    logging.LogError('plugin1.py -> Logging an error from Python plugin. --')

def OnPluginEnd():
    logging.LogMessage(f'plugin1.py -> OnPluginEnd: foobar.py')

def OnClientPutInServer(client):
    logging.LogMessage(f'plugin1.py -> OnClientPutInServer from Python: client -> {client} --')

def OnPluginLoaded(filename):
    #logging.LogMessage(f'OnPluginLoaded from Python: filename -> {filename}')
    pass

def OnEntityCreated(entity, classname):
    if classname == "survivor_bot":
        logging.LogMessage(f'plugin1.py -> Entity created: {entity}, classname: {classname} --')

count = 5
def OnGameFrame():
    global count
    if count > 0:
        logging.LogMessage('plugin1.py -> OnGameFrame: This message will be displayed 5 times.')
        count -= 1
