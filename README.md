# RAPPORT PROJET IOT 2022/2023
# Mesure d'occupation de salle et de niveau sonore

## Aide a la mise en forme 
```c
printf('mettre du code');
```

faire un tableau 
|Matériel|Quantité|Prix unitaire|Prix total|Remarques|
|--------|--------|-------------|----------|-|

insérer une image via le dossier img
![alt text](https://github.com/Chloeplt/Mesure-d-occupation-de-salle-niveau-sonore/blob/main/img/esp32.jpg?raw=true)

## Objectif - Chloe & Léo

L’objectif de notre projet est de mesurer de taux d'occupation d'une salle, ansi que son niveau sonore. La communication se fera avec un protocole Wifi et permettra de transmettre des payloads lourd dans un périmètre restraint.
Notre produit peut avoir de multiple utilité et donc de multiple client potentiel.
- Pour les salles de réunions des entreprises :
Savoir quelles salles sont disponible

- Pour les bibliothèques:

Permet aux utilisateurs de savoir si la bibliothèque permet une ambiance de travail optimal. Assez d'espace pour venir travailler, assez silencieux pour se concentrer.


- Pour les salle de concert, bar, salle de sport ect :



- Pour les supermarchées : 

Permet aux u

 L’objet LoRaWAN est identifié par son DevEUI et associé à une pièce ou à un lieu. Il peut être enregistré sur un réseau public national en OTAA ou sur un réseau privé en OTAA comme CampusIoT. Cet objet pourrait participer à un réseau maillé (“mesh”) LoRa (type Amazon Sidewalk).

L’objet sirène remonte régulièrement des mesures prises sur les capteurs (TH, smoke, CO,CO2...) équipant celui-ci au format LPP.

L’objet sirène est déclenché soit par un bouton poussoir (ie panic button), on utilisera ce bouton poussoir, soit par observation d’un événement “tragique” (changement “brutale” de la température, CO2, CO, fumée …) que l'on fera avec le capteur SCD30. Quand la sirène est munie d’un PIR Motion sensor, elle peut détecter et envoyer périodiquement la présence probable de personnes à proximité d’elle.

L’objet sirène envoie périodiquement un message de status (ie heart beat) une fois déclenchée.

Une vidéo de démonstration est disponible ici.

## Analyse de marché - Chloé
> Consigne : rechercher et analyser (avantages/inconvénients sous la forme d’une grille) des produits concurrents
> Consigne : réaliser une analyse (rapide) du marché des produits commerciaux concurrents

- Notr
## Architechture globale du système - Léo
> Consigne : définir l’architecture globale du systèmes (ensemble d’objets, service en ligne (cloud))

## Sécurité globale - Chloé
> Consigne : définir la sécurité globale (clé de chiffrage)

## Respect de la vie privée du service - Léo
> Consigne : définir le respect de la vie privée du service ([RGPD](https://www.cnil.fr/fr/reglement-europeen-protection-donnees)) : lister les risques d’atteinte au respect de la vie privée

## Architecture matérielle de l'objet - Chloé
> Consigne : définir l’architecture matérielle de l’objet,

## Coût de la BOM du produit - Léo
> Consigne : 
> estimer le coût de la BOM de votre produit (composants, PCB et enclosure) pour 5000 unités produites
. pour le boitier, vous pouvez rechercher des boitiers “standards” disponibles dans les catalogues fournisseurs
. pour le PCB, vous pouvez fournir une estimation du prix de fabrication du PCB et du masque chez des fournisseurs comme [https://jlcpcb.com/](https://jlcpcb.com/) , [https://www.wedirekt.fr/fr/](https://www.wedirekt.fr/fr/) …

## Coût de certification ETSI du produit - Chloé
> Consigne : estimer le coût de certification ETSI du produit, le coût de [certification LoRa Alliance](https://lora-alliance.org/lorawan-certification/) du produit ...

## Implémentation du logiciel embarqué - Léo 
> Consigne : proposer une implémentation du logiciel embarqué de l’objet défini.

## Format des messages Uplink et Downlink - Chloé
> Consigne : définir/documenter le format des messages uplink et downlink échangés (dans le cas des objets LoRaWAN, privilégiez le format LPP)

## Logiciel embarqué de l'objet - Léo
> Consigne : définir le logiciel embarqué de l’objet.

## Métrique logiciel
> Consigne : donner les métriques logiciel du logiciel embarqué (nombre de lignes de code, taille du binaire du firmware ie le fichier .bin)
> Consigne :  compter le nombre de lignes de code développé (coté objet, coté application) avec un outil comme [cloc](https://github.com/AlDanial/cloc). Précisez les langages et les outils utilisés (git, arduino-cli …)

## Instrumentation du logiciel embarqué
> Consigne : Instrumenter le logiciel embarqué pour mesurer les différents temps d’exécution des principales phases d’exécution (par exemple: durée d’une prise de photo, écriture sur carte SD, inférences avec un réseau de neurones …)
Prévoir de montrer la trace console de l’objet pendant la démonstration.

## Durée de vie de la batterie
> Consigne : estimer la durée de vie de la batterie de l’objet (pour LoRaWAN en fonction du datarate comme avec l’outil [https://www.elsys.se/en/battery-life-calculator/](https://www.elsys.se/en/battery-life-calculator/)

## Analyse du cycle de vie du produit 
> Consigne : réaliser une analyse (brève) du cycle de vie du produit “durable” et “[sobre](https://www.youtube.com/watch?v=aX_tzI7w7Qo)” ([ACV](https://fr.wikipedia.org/wiki/Analyse_du_cycle_de_vie))

## Montrer les intégrations effectuées
> Consigne : montrer les intégrations effectuées (cayenne, influxdb, home assistant, jupyter notebook …)



