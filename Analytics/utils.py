import os
import matplotlib.pyplot as plt
import numpy as np
from datetime import datetime

def getCurrentTime():
    return datetime.now().strftime("%H-%M-%S_%d-%m-%Y")

def levelValues(levelDF, event_type_map):
    counts = []
    for code in event_type_map.values():
        count = len(levelDF[levelDF["eType"] == code])
        counts.append(count)

    return np.array(counts)

def createFolder():
    folder = f"Graphics_{getCurrentTime()}"
    folder_path = os.path.join("results", folder)
    os.makedirs(folder_path, exist_ok=True)
    return folder_path

def createGraphic(categories, values, graphic_title, image_title, folder):
    colors = plt.cm.viridis(np.linspace(0, 1, len(categories))) 
    plt.bar(categories, values, color=colors)

    plt.title(graphic_title)
    plt.xlabel('Event')
    plt.ylabel('Mean value')

    name = image_title + f"_{getCurrentTime()}.png"
    path = os.path.join(folder, name)
    plt.savefig(path)
    plt.close()
    print("Graphic created and saved in: ", path)

def convertValues(df_sorted):
    data_converted = df_sorted.copy()
    data_converted['eType'] = data_converted['eType'].map({0: 'START_SESSION', 1:'END_SESSION', 2:'START_LEVEL', 3:'END_LEVEL', 4:'CARD_CHANGED',
                                                 5:'ABILITY_USED', 6:'PLAYER_HEALED', 7:'MANA_TAKEN', 8:'NOT_ENOUGHT_MANA', 9:'LEVEL_EXIT_POSSIBLE',
                                                 10:'LEAVE_FAILED', 11:'MOVED_FROM_HAND', 12:'MOVED_TO_HAND', 13:'INVENTORY_LEFT'})
    return data_converted

def getEventTypeMap():
    event_type_map = { 4:'CARD_CHANGED', 5:'ABILITY_USED',
                  8:'NOT_ENOUGHT_MANA', 9:'LEVEL_EXIT_POSSIBLE',
                  10:'LEAVE_FAILED'}
    return event_type_map

def getLevelEventIndexes():
    return {4, 5, 6, 7, 8, 9, 10}

def getInventoryTypeMap():
    inventory_type_map = { 11:'MOVED_FROM_HAND', 12:'MOVED_TO_HAND'}
    return inventory_type_map

def getInventoryIndexes():
    return {11, 12}