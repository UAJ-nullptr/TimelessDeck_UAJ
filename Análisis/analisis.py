import glob
import numpy as np
import pandas as pd
from loader import Loader

def levelValues(levelDF, event_type_map):
    counts = []
    for code in event_type_map.values():
        count = len(levelDF[levelDF["eType"] == code])
        counts.append(count)

    return np.array(counts)

def calculateOvertime(levelDF, level_end_event):
    if (level_end_event['win'] == "false"):
        return -1

    possibleEndEvents = levelDF[levelDF["eType"] == "LEVEL_EXIT_POSSIBLE"]
    if (len(possibleEndEvents) == 0):
        return -1
    endTS = level_end_event['timeStamp']
    firstPossibleEndEvent = possibleEndEvents.iloc[0]
    endPossibleTS = firstPossibleEndEvent['timeStamp']
    overtime = endTS - endPossibleTS
    overtimeValue = overtime.total_seconds()
    return overtimeValue

def calculateEffectiveHeal(levelDF):
    healing_events = levelDF[levelDF["eType"] == "PLAYER_HEALED"]
    return np.mean(((healing_events['lifeAfterHeal'] - healing_events['lifeBeforeHeal']) / healing_events['attemptedHeal']).to_numpy())

def calculateMana(levelDF):
    mana_events = levelDF[levelDF["eType"] == "MANA_TAKEN"]
    return np.mean((mana_events['manaAfter'] - mana_events['manaBefore']).to_numpy())

def meanSession(sessionDF, event_types):
    level_start_event = sessionDF[sessionDF["eType"] == "START_LEVEL"]
    level_end_event = sessionDF[sessionDF["eType"] == "END_LEVEL"]

    if len(level_start_event) != len(level_end_event):
        raise ValueError("Mismatch between START_LEVEL and END_LEVEL events")
    event_counters = []
    level_overtime = []
    effective_healing = []
    effective_mana_taken = []

    for i in range(len(level_start_event)):
        # Aislamos la parte del dataframe del nivel i
        level_start_time = level_start_event['timeStamp'].iloc[i]
        level_end_time = level_end_event['timeStamp'].iloc[i]
        levelDF = sessionDF[(sessionDF["timeStamp"] > level_start_time) & (sessionDF["timeStamp"] < level_end_time)]
        # Media de eventos
        event_counters.append(levelValues(levelDF, event_types))
        # Media de curacion efectiva y mana recogido
        effective_healing.append(calculateEffectiveHeal(levelDF))
        effective_mana_taken.append(calculateMana(levelDF))
        # Media de tiempo entre END_LEVEL - LEVEL_EXIT_POSSIBLE
        overtime = calculateOvertime(levelDF, level_end_event.iloc[i])
        if (overtime >= 0):
            level_overtime.append(overtime)
    event_mean = np.mean(np.array(event_counters), axis=0)
    overtime_mean = np.mean(np.array(level_overtime), axis=0)
    return event_mean, overtime_mean

def calculateAnalitics(df_sorted, event_types, inventory_types):
    game_start_events = df_sorted[df_sorted["eType"] == "START_SESSION"]
    game_end_events = df_sorted[df_sorted["eType"] == "END_SESSION"]
    events_means = []
    inventory_means = []
    overtime_means = []

    for i in range(len(game_start_events)):
        # Aislamos la parte del dataframe de la sesion i
        session_start_time = game_start_events['timeStamp'].iloc[i]
        session_end_time = game_end_events['timeStamp'].iloc[i]
        sessionDF = df_sorted[(df_sorted["timeStamp"] > session_start_time) & (df_sorted["timeStamp"] < session_end_time)]
        # Medias de los eventos en nivel - Partida

        session_event_means, session_overtime_means = meanSession(sessionDF, event_types)
        events_means.append(session_event_means)
        overtime_means.append(session_overtime_means)
        # Medias de los eventos en sesion - Inventario
        inventory_means.append(levelValues(sessionDF, inventory_types))
    event_mean = np.mean(np.array(events_means), axis=0)
    overtime_mean = np.mean(np.array(overtime_means), axis=0)

    return event_mean, overtime_mean

def convertValues(df_sorted):
    data_converted = df_sorted.copy()
    data_converted['eType'] = data_converted['eType'].map({0: 'START_SESSION', 1:'END_SESSION', 2:'START_LEVEL', 3:'END_LEVEL', 4:'CARD_CHANGED',
                                                 5:'ABILITY_USED', 6:'PLAYER_HEALED', 7:'MANA_TAKEN', 8:'NOT_ENOUGHT_MANA', 9:'LEVEL_EXIT_POSSIBLE',
                                                 10:'LEAVE_FAILED', 11:'MOVED_FROM_HAND', 12:'MOVED_TO_HAND', 13:'INVENTORY_LEFT'})
    return data_converted

loader = Loader("TimlessDeck-15724-1745417392410329000.json", False)

dataSorted = loader.data

dataSorted = dataSorted.sort_values("timeStamp")
# Display all rows of the DataFrame
pd.set_option("display.max_rows", None)

event_type_map = { 4:'CARD_CHANGED', 5:'ABILITY_USED',
                  8:'NOT_ENOUGHT_MANA', 9:'LEVEL_EXIT_POSSIBLE',
                  10:'LEAVE_FAILED'
}

inventory_type_map = { 11:'MOVED_FROM_HAND', 12:'MOVED_TO_HAND'}

# Sacar la media
dataSorted = convertValues(dataSorted)
means, overtime_mean = calculateAnalitics(dataSorted, event_type_map, inventory_type_map) # Se reemplazara por event_type_map
print(means)
print(overtime_mean)
# display(means)