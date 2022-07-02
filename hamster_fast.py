#-*-coding:UTF-8 -*
import math
import random
import sys
import os

#import matplotlib as plt

az = int(input())
arg_l = []
cage_l = []


for xpartie in range (0,az) :

    adultmale = 1
    adultfem = 1
    enfantmale = 0
    enfantfem = 0
    enfantmale2 = 0
    enfantfem2 = 0
    ventemale = 0
    ventefem = 0
    achatcage = 0
    achatnour = 0
    argent = 1000
    nourriture = 1
    nourrituretour = 0.1
    hamsternour = 0
    testEmale = 0
    testEfem = 0
    mortsup = 0
    enfant = 0
    pourcentage = 0
    newenfant = 0
    maxenfant = 0
    minenfant = 0
    fertilemax = 10
    fertilemin = 2
    tempargent = 0
    cage = 1
    pxcage = 100
    couple = 0
    placecage = 10
    reponse = 'true'
    placedispo = 0
    tour = 0
    x = 0

    scorepapa = 1058986
    scoresimon = 0



# Affichage
    annee = 0
    for tour in range(0, 104):
        annee = 0
        if tour%52==0:
            annee+=1
            print(annee)
        tour += 1
        pxhamster = random.randint(10, 30)
        pxnourriture = random.randint(5, 20) 

        adultmale = adultmale + enfantmale2
        adultfem = adultfem + enfantfem2
        enfantmale2 = enfantmale
        enfantfem2 = enfantfem
        totalhamster = adultmale + adultfem + enfantmale2 + enfantfem2

    
    # Ventes ou achats
        tempargent = argent
        # Males à vendre
        ventemale = int(adultmale * (3/4) * (1 /(1+math.exp(-(pxhamster-20)/20)))) #random.randint(0,adultmale - 1)
        # Femelles à vendre
        ventefem = int(adultfem * (3/4) * (1 /(1+math.exp(-(pxhamster-20)/20))))    #random.randint(0,adultfem - 1)
        tempargent = tempargent + (ventefem + ventemale) * pxhamster
        # Cages à acheter                
        achatcage = int(tempargent/200) #random.randint(int(tempargent/400),int(3*tempargent/400))
        tempargent = tempargent - (achatcage * pxcage)
        # Nourriture à acheter       
        achatnour = round((cage+achatcage)* (1/(1+math.exp((pxnourriture-12.5))) - 1/4)*1/2 + cage+achatcage)
        if (achatnour*pxnourriture)>=tempargent:
            achatnour = int(tempargent/pxnourriture) -1
                #random.randint(1,int (tempargent/pxnourriture))
        tempargent = tempargent - achatnour * pxnourriture
        # Sortie des questions
    # Calculs  
        argent = tempargent
        cage = cage + achatcage
        nourriture = nourriture + achatnour
        adultmale = adultmale - ventemale
        adultfem = adultfem - ventefem
        if adultmale < adultfem:
            couple = adultmale
        else:
            couple = adultfem    
        maxenfant = fertilemax * couple
        minenfant = fertilemin * couple
        newenfant = random.randint(minenfant, maxenfant)    
        placedispo = placecage * cage
        totalhamster = newenfant + adultmale + adultfem + enfantmale2 + enfantfem2
        if totalhamster < placedispo:
            pass
        elif totalhamster > placedispo:
            mort = totalhamster - placedispo
            if mort != 0:
               newenfant = newenfant - mort
            else:
                pass
        totalhamster = newenfant + adultmale + adultfem + enfantmale2 + enfantfem2
        hamsternour = (nourriture / nourrituretour)
        mort = int(totalhamster - hamsternour)
        if mort < 0:
            mort = 0
        nourriture = round((nourriture - (totalhamster - mort) * nourrituretour)*10)/10    
        if mort <= totalhamster and mort != 0:
            #print("a")
            while True:            
                if newenfant == 0 and adultmale != 0 and adultfem != 0:                
                    while True:
                         if adultmale != 0 and mort != 0:
                            adultmale -= 1
                            mort -= 1                        
                            pass                    
                         if adultfem != 0 and mort != 0:
                            adultfem = adultfem - 1
                            mort = mort - 1                        
                            pass
                         if mort == 0:
                            break
                         elif adultmale == 0 and adultfem == 0:
                            break
                elif newenfant != 0:                                
                    while True:
                        if newenfant != 0 and mort != 0:
                            newenfant = newenfant - 1
                            mort = mort - 1
                            pass
                        else:
                            break
                elif newenfant == 0 and adultmale == 0 and adultfem == 0:                
                    while True:
                         if enfantmale2 != 0 and mort != 0:
                            enfantmale2 = enfantmale2 - 1
                            mort = mort - 1
                            pass
                         else:
                            pass
                         if enfantfem2 != 0 and mort != 0:
                            enfantfem2 = enfantfem2 - 1
                            mort = mort - 1
                            pass
                         else:
                            pass
                         if mort == 0:
                            break
                         elif enfantmale2 == 0 and enfantfem2 == 0:
                            break
                if mort == 0:
                    break
                elif enfantmale2 == 0 and enfantfem2 == 0:
                    break
                else:
                    pass
        pourcentage = random.randint(3, 7)
        enfantmale = round(pourcentage * newenfant / 10)
        enfantfem = newenfant - enfantmale    
        enfantmale = int(enfantmale)
        enfantfem = int(enfantfem)
        if enfantmale == 0 and enfantfem == 0 and adultmale == 0 and adultfem == 0 and enfantmale2 == 0 and enfantfem2 == 0:
            break        
    if enfantmale == 0 and enfantfem == 0 and adultmale == 0 and adultfem == 0 and enfantmale2 == 0 and enfantfem2 == 0 and tour != 0:
            print("tu as perdu, tu ne possède plus aucun hamster")
            print("GAME OVER")
    argent += (enfantmale + enfantfem + adultmale + adultfem)*20
    #print("Bravo, tu as passer 52 semaines")
    print("tu as obtenu %s m $.felicitation." % (argent/1000000))
    print("Et tu a obtenu ",(cage/1000))
    #print("   ")
    print("   ")

    #arg_l.append(argent/1000000)
    #cage_l.append(cage/1000)
