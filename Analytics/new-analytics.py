import glob
import sys
import numpy as np
import pandas as pd
import matplotlib as plt
from EventLibrary import EventLibrary
from utils import createFolder, createGraphic

event_map = {0: 'START_SESSION', 1:'END_SESSION', 2:'START_LEVEL', 3:'END_LEVEL', 4:'CARD_CHANGED',
                                                 5:'ABILITY_USED', 6:'PLAYER_HEALED', 7:'MANA_TAKEN', 8:'NOT_ENOUGHT_MANA', 9:'LEVEL_EXIT_POSSIBLE',
                                                 10:'LEAVE_FAILED', 11:'MOVED_FROM_HAND', 12:'MOVED_TO_HAND', 13:'INVENTORY_LEFT'}
library = EventLibrary('telemetry_data', event_map.__len__())

# print("\n")
# folder = createFolder()

# categories = ['Card Changes', 'Abilities used']
# createGraphic(categories, event_means[:2], '¿El jugador entiende el funcionamiento de las cartas?', 'Card_Mechanics',  folder)

# categories = ['Effective healing (percentage)', 'Effective mana (percentage)']
# createGraphic(categories, [healing_mean, mana_taken_mean], '¿El jugador entiende las tres barras superiores? - Cambios efectivos', 'UI_Understanding_Effective_Changes', folder)

# categories = ['Failed ability attemps', 'Successful ability uses']
# createGraphic(categories, [event_means[2], successful_ability_uses], '¿El jugador entiende las tres barras superiores? - Habilidades', 'UI_Understanding_Abilities', folder)

# categories = ['Overtime per level', 'Failed level exits']
# createGraphic(categories, [overtime_mean, event_means[4]], '¿El jugador entiende qué tiene que hacer para salir del nivel, y cuándo lo puede hacer?', 'Exit_Level', folder)

# categories = ['Deck reductions', 'Deck additions', 'Effective changes in deck']
# createGraphic(categories, [inventory_mean[0], inventory_mean[1], deck_change_mean], '¿Entiende el jugador como gestionar sus cartas?', 'Card_Management', folder)