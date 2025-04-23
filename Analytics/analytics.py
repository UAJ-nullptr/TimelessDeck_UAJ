import glob
import sys
import numpy as np
import pandas as pd
import matplotlib as plt
from loader import Loader
from utils import convertValues, createGraphic, levelValues, getEventTypeMap, getInventoryTypeMap
from event_metrics import calculateEffectiveHeal, calculateOvertime, calculateDeckDiffs, calculateMana

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
    effective_healing_mean = np.mean(np.array(effective_healing), axis=0)
    effective_mana_taken_mean = np.mean(np.array(effective_mana_taken), axis=0)
    return event_mean, overtime_mean, effective_healing_mean, effective_mana_taken_mean

def calculateAnalitics(df_sorted, event_types, inventory_types):
    game_start_events = df_sorted[df_sorted["eType"] == "START_SESSION"]
    game_end_events = df_sorted[df_sorted["eType"] == "END_SESSION"]
    events_means = []
    inventory_means = []
    overtime_means = []
    effective_healing_means = []
    effective_mana_taken_means = []
    deck_diffs = []

    for i in range(len(game_start_events)):
        # Aislamos la parte del dataframe de la sesion i
        session_start_time = game_start_events['timeStamp'].iloc[i]
        session_end_time = game_end_events['timeStamp'].iloc[i]
        sessionDF = df_sorted[(df_sorted["timeStamp"] > session_start_time) & (df_sorted["timeStamp"] < session_end_time)]
        # Medias de los eventos en nivel - Partida

        session_event_means, session_overtime_means, effective_healing_mean, effective_mana_taken_mean  = meanSession(sessionDF, event_types)
        deck_diffs.append(calculateDeckDiffs(sessionDF))
        events_means.append(session_event_means)
        overtime_means.append(session_overtime_means)
        effective_healing_means.append(effective_healing_mean)
        effective_mana_taken_means.append(effective_mana_taken_mean)
        # Medias de los eventos en sesion - Inventario
        inventory_means.append(levelValues(sessionDF, inventory_types))
    event_mean = np.mean(np.array(events_means), axis=0)
    overtime_mean = np.mean(np.array(overtime_means), axis=0)
    inventory_mean = np.mean(np.array(inventory_means), axis=0)
    deck_change_mean = np.mean(np.array(deck_diffs), axis=0)
    healing_mean = np.mean(np.array(effective_healing_means), axis=0)
    mana_taken_mean = np.mean(np.array(effective_mana_taken_means), axis=0)
    return event_mean, overtime_mean, inventory_mean, healing_mean, mana_taken_mean, deck_change_mean

loader = Loader("telemetry_data", True)

dataSorted = loader.data

dataSorted = dataSorted.sort_values("timeStamp")

# Sacar la media
dataSorted = convertValues(dataSorted)
event_means, overtime_mean, inventory_mean, healing_mean, mana_taken_mean, deck_change_mean = calculateAnalitics(dataSorted, getEventTypeMap(), getInventoryTypeMap())

print("---------EVENT METRICS----------\n")
print("Average card changes per level:", event_means[0])
print("Average skill uses per level:", event_means[1])
print("Average attempts at skill without mana (per level):", event_means[2])
print("Average attempts at leaving without full charge (per level):", event_means[4])

print("\n\n---------INVENTORY METRICS----------\n")
print("Deck reductions per session:", inventory_mean[0])
print("Deck additions per session:", inventory_mean[1])
print("Average deck changes per session:", deck_change_mean)

successful_ability_uses = event_means[1] / (event_means[1] + event_means[2]) * 100
print("\n\n---------BATTLE METRICS----------\n")
print("Overtime average: ", overtime_mean, "s")
print("Effective healing%: ", healing_mean * 100)
print("Effective mana taking%: ",mana_taken_mean * 100)
print("Successful abilities usage%: ", successful_ability_uses)

categories = ['Card Changes', 'Abilities used']
createGraphic(categories, event_means[:2], '¿El jugador entiende el funcionamiento de las cartas?')

categories = ['Effective healing (percentage)', 'Failed ability attemps', 'Successful ability uses', 'Effective mana (percentage)']
createGraphic(categories, [healing_mean, event_means[2], successful_ability_uses, mana_taken_mean], '¿El jugador entiende las tres barras superiores?')

categories = ['Overtime per level', 'Failed level exits']
createGraphic(categories, [overtime_mean, event_means[4]], '¿El jugador entiende qué tiene que hacer para salir del nivel, y cuándo lo puede hacer?')

categories = ['Deck reductions', 'Deck additions', 'Effective changes in deck']
createGraphic(categories, [inventory_mean[0], inventory_mean[1], deck_change_mean], '¿Entiende el jugador como gestionar sus cartas?')