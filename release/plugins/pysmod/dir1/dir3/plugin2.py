from sourcemod import logging

PYSMOD_PLUGIN = True

def OnPluginEnd():
    logging.LogMessage(f'OnPluginEnd: plugin2.py')
