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

if len(library.getEventList(0)) == 0 or len(library.getEventList(1)) == 0 or len(library.getEventList(2)) == 0 or len(library.getEventList(3)) == 0:
    sys.exit()

folder = createFolder()

means = []
for event_type in getEventIndexes():
    means.append(getMean(library, event_type))

print("---------EVENT METRICS----------")
print(f"Average card changes per level: {means[0]:.2f}")
print(f"Average skill uses per level: {means[1]:.2f}")
print(f"Average attempts at skill without mana (per level): {means[4]:.2f}")
print(f"Average attempts at leaving without full charge (per level): {means[6]:.2f}")

print("\n---------INVENTORY METRICS----------")
print(f"Deck reductions per session: {means[7]:.2f}")
print(f"Deck additions per session: {means[8]:.2f}")
print(f"Average deck changes per session: {means[9]:.2f}")

successful_ability_uses = 0
if (means[1] + means[4]) != 0:
    successful_ability_uses = means[1] / (means[1] + means[4])

print("\n---------BATTLE METRICS----------")
print(f"Overtime average: {means[5]:.2f}s")
print(f"Effective healing: {means[2] * 100:.2f}%")
print(f"Effective mana taking: {means[3] * 100:.2f}%")
print(f"Successful abilities usage: {successful_ability_uses*100:.2f}%")
print('\n')

categories = ['Card Changes', 'Abilities used']
createGraphic(categories, means[:2], 'Card-related metrics', 'Card_Mechanics',  folder)

categories = ['Effective healing (percentage)', 'Effective mana (percentage)']
createGraphic(categories, means[2:4], 'UI - Effective Changes', 'UI_Understanding_Effective_Changes', folder)

categories = ['Successful ability uses', 'Failed ability attemps']
createGraphic(categories, [successful_ability_uses, means[4]], 'UI - Abilities', 'UI_Understanding_Abilities', folder)

categories = ['Overtime per level - in seconds', 'Failed level exits']
createGraphic(categories, means[5:7], 'LevelExit-related metrics', 'Exit_Level', folder)

categories = ['Deck reductions', 'Deck additions', 'Effective changes in deck']
createGraphic(categories, means[7:], 'CardManagement-related metrics', 'Card_Management', folder)