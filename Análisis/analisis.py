import glob
import numpy as np
import pandas as pd
from loader import Loader

def levelValues(levelDF, event_type_map):
    counts = []
    for code in event_type_map.keys():
        count = len(levelDF[levelDF["eventType"] == code]) # Cambiar por eType cuando haya telemetria
        counts.append(count)

    return np.array(counts)

def meanSession(sessionDF, event_types):
    level_start_event = sessionDF[sessionDF["eventType"] == "LEVEL:START"]
    level_end_event = sessionDF[sessionDF["eventType"] == "LEVEL:END"]
    event_counters = []

    # Sera reemplazado por 
    # level_start_event = sessionDF[sessionDF["eType"] == "START_LEVEL"]
    # level_end_event = sessionDF[sessionDF["eType"] == "END_LEVEL"]

    for i in range(len(level_start_event)):
        level_start_time = level_start_event['timestamp'].iloc[i]
        level_end_time = level_end_event['timestamp'].iloc[i]
        levelDF = sessionDF[(sessionDF["timestamp"] > level_start_time) & (sessionDF["timestamp"] < level_end_time)]
        event_counters.append(levelValues(levelDF, event_types))
    return np.mean(np.array(event_counters), axis=0)

def calculateMean(df_sorted, event_types):
    game_start_events = df_sorted[df_sorted["eventType"] == "GAME:START"]
    game_end_events = df_sorted[df_sorted["eventType"] == "GAME:END"]
    events_counters = []
    
    # Sera reemplazado por 
    #game_start_events = df_sorted[df_sorted["eType"] == "START_SESSION"]
    #game_end_events = df_sorted[df_sorted["eType"] == "END_SESSION"]

    for i in range(len(game_start_events)):
        session_start_time = game_start_events['timestamp'].iloc[i]
        session_end_time = game_end_events['timestamp'].iloc[i]
        sessionDF = df_sorted[(df_sorted["timestamp"] > session_start_time) & (df_sorted["timestamp"] < session_end_time)]
        events_counters.append(meanSession(sessionDF, event_types))
    return np.mean(np.array(events_counters), axis=0)

def convertValues(df_sorted):
    data_converted = df_sorted.copy()
    data_converted['eType'] = data_converted['eType'].map({0: 'START_SESSION', 1:'END_SESSION', 2:'START_LEVEL', 3:'END_LEVEL', 4:'CARD_CHANGED', 
                                                 5:'ABILITY_USED', 6:'PLAYER_HEALED', 7:'PERIODIC_HEALTH_STATUS', 8:'MANA_TAKEN', 9:'NOT_ENOUGHT_MANA',
                                                 10:'LEVEL_EXIT_POSSIBLE', 11:'TRIED_LEAVING', 12:'MOVED_FROM_HAND', 13:'MOVED_TO_HAND', 14:'INVENTORY_LEFT'})
    return data_converted

loader = Loader("telemetry.json", False)

dataSorted = loader.data

dataSorted = dataSorted.sort_values("timestamp")
# Display all rows of the DataFrame
pd.set_option("display.max_rows", None)

event_type_map = { 4: 'CARD_CHANGED', 5: 'ABILITY_USED', 6: 'PLAYER_HEALED', 7: 'PERIODIC_HEALTH_STATUS',
    8: 'MANA_TAKEN', 9: 'NOT_ENOUGHT_MANA', 10: 'LEVEL_EXIT_POSSIBLE',
    11: 'TRIED_LEAVING', 12: 'MOVED_FROM_HAND', 13: 'MOVED_TO_HAND', 14: 'INVENTORY_LEFT'
}

# Sacar la media
#dataSorted = convertValues(dataSorted)
means = calculateMean(dataSorted, event_types={'PLAYER:DEATH':0}) # Se reemplazara por event_type_map
print(means)
# display(means)