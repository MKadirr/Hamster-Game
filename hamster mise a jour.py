#-*-coding:UTF-8 -*

import random
import sys
import os
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
for tour in range(0, 53):
    tour += 1
    pxhamster = random.randint(10, 30)
    pxnourriture = random.randint(5, 20) 

    adultmale = adultmale + enfantmale2
    adultfem = adultfem + enfantfem2
    enfantmale2 = enfantmale
    enfantfem2 = enfantfem
    totalhamster = adultmale + adultfem + enfantmale2 + enfantfem2
    
    print("       ")
    print("C'est le tour %s" % tour)
    print("Vous possédez:")
    print("   %s $" % argent)
    print("   %s adultes males" % adultmale)
    print("   %s adultes femmelles" % adultfem)
    print("   %s enfants males" % enfantmale2)
    print("   %s enfants femelles" % enfantfem2)
    print("   %s hamsters au total" % totalhamster)
    print("   %s kg de nourriture" % nourriture)
    print("   %s cages" % cage)
    print("    ")
    print("les prix du jour sont:")
    print("   les cages coutent %s $" % pxcage)
    print("   la nourriture coute %s $ le kg" % pxnourriture)
    print("   les hamsters adultes valent %s $" % pxhamster)

    
    # Ventes ou achats
    a = 0
    while a < 10:
        tempargent = argent


        # Males à vendre

        print("    ")
        try:
            print(" Combien de males veux tu vendre ?")    
            for x in range(0, 100):
                choix = input()
                if not bool(choix.rstrip()):
                    print("tu doit entrer une valeur !!!")
                    pass
                else:
                    choix = int(choix)
                    if choix > adultmale:
                        print("Tu n'as pas assez de males adultes, recommence :")
                    else:
                        ventemale = choix
                        break
        except ValueError:
            print("Tu ne peux entrer que des chiffres")
            continue


        # Femelles à vendre
        print("    ")
        for x in range(0, 10000):
            try:
                print(" Combien de femmelles veux tu vendre ?")    
                choix = input()
                if not bool(choix.rstrip()):
                   print("tu doit entrer une valeur !!!")
                   pass
                else:
                   choix = int(choix)
                   if choix > adultfem:
                     print("Tu n'as pas assez de femmelles adultes, recommence :")
                   else:
                      ventefem = choix
                      break
            except ValueError:
                print("Tu ne peux entrer que des chiffres")
                continue        

        tempargent = tempargent + (ventefem + ventemale) * pxhamster
        print("tu as desormais %s $" %tempargent)


        # Cages à acheter    
        print("    ")
        for x in range(0, 10000):
            try:
                print(" combien de cage veux tu acheter ? sachant qu'une cage coute %s $" % pxcage)             
                choix = input()

                if not bool(choix.rstrip()):
                   print("tu doit entrer une valeur !!!")
                   pass
                else:
                   choix = int(choix)
                   if choix * pxcage > tempargent:
                      print("Tu n'as pas assez d'argent, recommence :")
                   else:
                      achatcage = choix
                      print("tu as acheté %s cages" % choix)
                      break

            except ValueError:
                print("Tu ne peux entrer que des chiffres")
                continue


        tempargent = tempargent - choix * pxcage
        print("tu as desormais %s $" %tempargent)

        # Nourriture à acheter   
        print("    ")
        for x in range(0, 10000):
            try:
                print(" Quelle quantité de nourriture veux tu ? sachant que le kg vaut %s $" % pxnourriture) 
                choix = input()
                if not bool(choix.rstrip()):
                   print("tu doit entrer une valeur !!!")
                   pass
                else:
                    choix = float(choix)
                    if choix * pxnourriture > tempargent:
                        print("Tu n'as pas assez d'argent, recommence :")
                    else:
                        achatnour = choix
                        print("tu as acheté %s kg de nourriture" % choix)
                        break
    
            except ValueError:
                print("Tu ne peux entrer que des chiffres")
                continue

        tempargent = tempargent - choix * pxnourriture
        print("tu as desormais %s $" %tempargent)

        # Sortie des questions
        print("    ")
        if a > 9:
            print("tu ne peux plus recommencer")
            break
        else:
            print("tape r si tu veux recommencer sinon appuis sur entrée")
            reponse = input()
            #print(reponse)
            if reponse == "r":
                print("Retour au question")
                a = a + 1
            elif reponse != "r":
                print("    ")
                print("    ")
                print("    ")
                break

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



    #print("nouveaux enfants %s" % newenfant)
   
    
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




    #print("total hamster %s" % totalhamster)
    #print("nouveaux enfants survivants cages %s" % newenfant


    totalhamster = newenfant + adultmale + adultfem + enfantmale2 + enfantfem2
    hamsternour = (nourriture / nourrituretour)
    mort = int(totalhamster - hamsternour)
    if mort < 0:
        mort = 0

    #print("mort nourriture %s" % mort)
    nourriture = round((nourriture - (totalhamster - mort) * nourrituretour)*10)/10
    
    if mort <= totalhamster and mort != 0:                
        while True:
            if newenfant == 0:
                while True:
                     if adultmale != 0 and mort != 0:
                        adultmale = adultmale - 1
                        mort = mort - 1
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
            elif enfantmale2 == 0 and enfnatfem2 == 0:
                break
            else:
                pass
        



    #print("nouveaux enfants %s" % newenfant)
    #print("adultes femelles %s" % adultfem)
    #print("adultes males %s" % adultmale)
    #print("mort %s" % mort)
    pourcentage = random.randint(3, 7)
    enfantmale = round(pourcentage * newenfant / 10)
    enfantfem = newenfant - enfantmale
    #testEmale = enfantmale - int(enfantmale)
    #testEfem = enfantfem - int(enfantfem)
    #if testEmale > testEfem:
    #   enfantmale = enfantmale + 1
    #elif testEmale < testEfem:
    #   enfantfem = enfantfem + 1
    
    enfantmale = int(enfantmale)
    enfantfem = int(enfantfem)
    print("tu as eu %s enfants femmelles et %s enfants males" % (enfantfem, enfantmale))

    if enfantmale == 0 and enfantfem == 0 and adultmale == 0 and adultfem == 0 and enfantmale2 == 0 and enfantfem2 == 0:
        break

    print("   ")
    print("   ")
    print("   ")
    print("   ")
    print("   ")



if enfantmale == 0 and enfantfem == 0 and adultmale == 0 and adultfem == 0 and enfantmale2 == 0 and enfantfem2 == 0 and tour != 0:
        print("tu as perdu, tu ne possède plus aucun hamster")
        print("GAME OVER")
elif tour == 52:
    print("Bravo, tu as passer 52 semaines")
    print("tu as obtenu %s $.felicitation." % argent)
    
os.systeme("pause")

    
        
       






        
