import numpy as np
import pandas as pd
import json
import os

# Para calcular el numero de veces que ha cambiado el mazo del jugador vemos las diferencias entre envento. Si no hay eventos de dejar 
# el inventario marcamos como a no tener en cuenta esta sesion, pero si hay contamos uno cada vez que haya una diferencia entre mazos
# inventory_events = eventos con eType==13 (INVENTORY_LEFT)
# t_min = el timeStamp de inicio de sesion
# t_max = el timeStamp de fin de sesion
def calculateDeckDiffs(inventory_events, t_min, t_max):
    count = 0
    filtered_events = [e for e in inventory_events if t_min < e.get('timeStamp', 0) < t_max]
    if len(filtered_events) == 0:
        return {False, 0}

    for i in range(len(filtered_events)-1):
        if filtered_events[i].get('currentDeck') != filtered_events.get('currentDeck') :
            count += 1

    return {True, count / len(filtered_events) * 100}

# Para calcular la curacion efectiva realizada por el jugador vemos los atributos lifeBeforeHeal, lifeAfterHeal y attemptedHeal de cada evento para realizar calculos con ellos. Si no 
# hay eventos de cura marcamos este nivel para no tenerlo en cuenta. Si los eventos contienen informacion no valida o les falta un atributo, no los contamos. Luego hacemos la media
# heal_events = eventos con eType==6 (PLAYER_HEALED)
# t_min = el timeStamp de inicio de sesion
# t_max = el timeStamp de fin de sesion
def calculateEffectiveHeal(heal_events, t_min, t_max):
    filtered_events = [e for e in heal_events if t_min < e.get('timeStamp', 0) < t_max]
    if len(filtered_events) == 0:
        return {False, 0}
    
    stored_values = []
    for e in filtered_events:
        try:
            before = e.get('lifeBeforeHeal')
            after = e.get('lifeAfterHeal')
            attemp = e.get('attemptedHeal')

            if None in (before, after, attemp) or attemp == 0:
                continue

            effective_heal = (after - before) / attemp
            stored_values.append(effective_heal)

        except Exception as ex:
            continue

    if not stored_values:
        return {False, 0}
    media = sum(stored_values) / len(stored_values)
    return {True, media}

# Para calcular el tiempo extra que esta un jugador en un nivel primero vemos que el jugador haya podido salir de ese nivel (que haya ganado). Luego vemos la diferencia de timeStamps
# exit_level_events = eventos con eType==9 (LEVEL_EXIT_POSSIBLE)
# t_min = el timeStamp de inicio de nivel
# t_max = el timeStamp de fin de nivel
# level_end_event = evento de salida de nivel
def calculateOvertime(exit_level_events, t_min, t_max, level_end_event):
    filtered_events = [e for e in exit_level_events if t_min < e.get('timeStamp', 0) < t_max]

    if (level_end_event.get('win') == "false"):
        return  {False, 0}
    
    endTS = level_end_event.get('timeStamp')
    firstPossibleEndEvent = filtered_events[0]
    endPossibleTS = firstPossibleEndEvent.get('timeStamp')
    overtime = endTS - endPossibleTS
    overtimeValue = overtime.total_seconds()
    return {True, overtime}

# Para calcular las particulas efectivas de mana recogidas por el jugador en un nivel vemos la diferencia de mana antes y despues y dividimos entre 5 (lo que aporta cada particula)
# mana_events = eventos con eType==7 (MANA_TAKEN)
# t_min = el timeStamp de inicio de nivel
# t_max = el timeStamp de fin de nivel
def calculateMana(mana_events, t_min, t_max):
    filtered_events = [e for e in mana_events if t_min < e.get('timeStamp', 0) < t_max]

    if len(filtered_events) == 0:
        return {False, 0}
    
    stored_values = []
    for e in filtered_events:
        try:
            before = e.get('manaBefore')
            after = e.get('manaAfter')

            if None in (before, after):
                continue
            mana_taken = (after - before) / 5
            stored_values.append(mana_taken)

        except Exception as ex:
            continue

    if not stored_values:
        return {False, 0}
    media = sum(stored_values) / len(stored_values)
    return {True, media}

def meanSession(event_library, start_time, end_time):
    # Usamos los limites de timeStamp para aislar los eventos de la lista referentes a este nivel
    # Con esos eventos calculamos las medias que queremos (nuevo metodo en utils)
    # Se deben realizar calculos especificos (como la curacion, el mana y el overtime)
    return True