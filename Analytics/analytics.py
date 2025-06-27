import glob
import sys
import numpy as np
import pandas as pd
import matplotlib as plt
from EventLibrary import EventLibrary
from utils import createFolder, createGraphic, getEventIndexes
from event_metrics import getMean

event_map = {0: 'START_SESSION', 1:'END_SESSION', 2:'START_LEVEL', 3:'END_LEVEL', 4:'CARD_CHANGED',
                                                 5:'ABILITY_USED', 6:'PLAYER_HEALED', 7:'MANA_TAKEN', 8:'NOT_ENOUGHT_MANA', 9:'LEVEL_EXIT_POSSIBLE',
                                                 10:'LEAVE_FAILED', 11:'MOVED_FROM_HAND', 12:'MOVED_TO_HAND', 13:'INVENTORY_LEFT'}
library = EventLibrary('telemetry_data', event_map.__len__())

folder = createFolder()

means = []
for event_type in getEventIndexes():
    means.append(getMean(library, event_type))

categories = ['Card Changes', 'Abilities used']
createGraphic(categories, means[:2], '¿El jugador entiende el funcionamiento de las cartas?', 'Card_Mechanics',  folder)

categories = ['Effective healing (percentage)', 'Effective mana (percentage)']
createGraphic(categories, means[2:4], '¿El jugador entiende las tres barras superiores? - Cambios efectivos', 'UI_Understanding_Effective_Changes', folder)

categories = ['Successful ability uses', 'Failed ability attemps']
createGraphic(categories, [means[1], means[4]], '¿El jugador entiende las tres barras superiores? - Habilidades', 'UI_Understanding_Abilities', folder)

categories = ['Overtime per level - in seconds', 'Failed level exits']
createGraphic(categories, means[5:7], '¿El jugador entiende cómo y cuando salir del nivel?', 'Exit_Level', folder)

categories = ['Deck reductions', 'Deck additions', 'Effective changes in deck']
createGraphic(categories, means[7:], '¿Entiende el jugador como gestionar sus cartas?', 'Card_Management', folder)