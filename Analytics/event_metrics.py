import numpy as np

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
    if len(healing_events) == 0:
        return 0
    return np.mean(((healing_events['lifeBeforeHeal'] - healing_events['lifeAfterHeal']) / healing_events['attemptedHeal']).to_numpy())

def calculateDeckDiffs(sessionDF):
    deck_change_events = sessionDF[sessionDF["eType"] == "INVENTORY_LEFT"]
    deck_change_arrays = deck_change_events["currentDeck"]

    lenght = len(deck_change_arrays)
    count = 0
    for i in range(lenght-1):
        if deck_change_arrays.iloc[i] != deck_change_arrays.iloc[i+1] :
            count += 1
    pass

    return count

def calculateMana(levelDF):
    mana_events = levelDF[levelDF["eType"] == "MANA_TAKEN"]
    if len(mana_events) == 0:
        return 0
    return np.mean(((mana_events['manaAfter'] - mana_events['manaBefore']) / 5).to_numpy())