import glob
import numpy as np
import pandas as pd
from loader import Loader

def levelValues(levelDF, event_type_map):
    counts = []
    for code in event_type_map.keys():
        count = len(levelDF[levelDF["eType"] == code]) # Cambiar por eType cuando haya telemetria
        counts.append(count)

    return np.array(counts)

def meanSession(sessionDF, event_types):
    level_start_event = sessionDF[sessionDF["eType"] == "START_LEVEL"]
    level_end_event = sessionDF[sessionDF["eType"] == "END_LEVEL"]

    if len(level_start_event) != len(level_end_event):
        raise ValueError("Mismatch between START_LEVEL and END_LEVEL events")
    event_counters = []

    # Sera reemplazado por
    # level_start_event = sessionDF[sessionDF["eType"] == "START_LEVEL"]
    # level_end_event = sessionDF[sessionDF["eType"] == "END_LEVEL"]

    for i in range(len(level_start_event)):
        level_start_time = level_start_event['timeStamp'].iloc[i]
        level_end_time = level_end_event['timeStamp'].iloc[i]
        levelDF = sessionDF[(sessionDF["timeStamp"] > level_start_time) & (sessionDF["timeStamp"] < level_end_time)]
        event_counters.append(levelValues(levelDF, event_types))
    return np.mean(np.array(event_counters), axis=0)

def calculateMean(df_sorted, event_types):
    #game_start_events = df_sorted[df_sorted["eType"] == "GAME:START"]
    #game_end_events = df_sorted[df_sorted["eType"] == "GAME:END"]

    # Sera reemplazado por
    game_start_events = df_sorted[df_sorted["eType"] == "START_SESSION"]
    game_end_events = df_sorted[df_sorted["eType"] == "END_SESSION"]
    events_counters = []

    for i in range(len(game_start_events)):
        session_start_time = game_start_events['timeStamp'].iloc[i]
        session_end_time = game_end_events['timeStamp'].iloc[i]
        sessionDF = df_sorted[(df_sorted["timeStamp"] > session_start_time) & (df_sorted["timeStamp"] < session_end_time)]
        events_counters.append(meanSession(sessionDF, event_types))
    return np.mean(np.array(events_counters), axis=0)

def convertValues(df_sorted):
    data_converted = df_sorted.copy()
    data_converted['eType'] = data_converted['eType'].map({0: 'START_SESSION', 1:'END_SESSION', 2:'START_LEVEL', 3:'END_LEVEL', 4:'CARD_CHANGED',
                                                 5:'ABILITY_USED', 6:'PLAYER_HEALED', 7:'PERIODIC_HEALTH_STATUS', 8:'MANA_TAKEN', 9:'NOT_ENOUGHT_MANA',
                                                 10:'LEVEL_EXIT_POSSIBLE', 11:'TRIED_LEAVING', 12:'MOVED_FROM_HAND', 13:'MOVED_TO_HAND', 14:'INVENTORY_LEFT'})
    return data_converted

loader = Loader("TimlessDeck-12036-1745274911802608300.json", False)

dataSorted = loader.data

dataSorted = dataSorted.sort_values("timeStamp")
# Display all rows of the DataFrame
pd.set_option("display.max_rows", None)

event_type_map = { 4: 'CARD_CHANGED', 5: 'ABILITY_USED', 6: 'PLAYER_HEALED', 7: 'PERIODIC_HEALTH_STATUS',
    8: 'MANA_TAKEN', 9: 'NOT_ENOUGHT_MANA', 10: 'LEVEL_EXIT_POSSIBLE',
    11: 'TRIED_LEAVING', 12: 'MOVED_FROM_HAND', 13: 'MOVED_TO_HAND', 14: 'INVENTORY_LEFT'
}

# Sacar la media
dataSorted = convertValues(dataSorted)
means = calculateMean(dataSorted, event_type_map) # Se reemplazara por event_type_map
print(means)
# display(means)