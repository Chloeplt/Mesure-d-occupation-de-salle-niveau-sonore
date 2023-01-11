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
Le système est composé d’un WIO Terminal, d’un ESP32-EYE et d’un capteur de présence PIR. 
L’ESP32-EYE est un capteur embarquant une caméra et un microphone. Il communiquera avec le Wio Terminal grâce au protocole Wifi. Le capteur PIR sera utilisé pour détecter la présence de quelqu’un et communiquera directement avec le Wio Terminal sur lequel il sera branché. Enfin nous utiliserons des éléments directement présent sur le Wio Terminal tel qu’une LED, les boutons pour avoir plusieurs mods de fonctionnement (mode normal, mode économie d'énergie, mode débogage), ainsi que l’écran d’affichage si besoin, cela dépendra de l’autonomie souhaité et du mode en cours d’utilisation. Pour le mode normal il sera possible d’afficher des données en temps réel et l’écran pourra être utile pour le mode débogage car on pourra afficher plus de variables.
Le principe de fonctionnement est le suivant. Lorsque le capteur de présence PIR détecte un mouvement, il allume la caméra et la lumière. Cette dernière est ici représentée par la LED du Wio Terminal. La caméra (embarqué sur l’ESP32-EYE) prend alors le relais pour détecter la présence d’individus. Elle prend une photo toutes les minutes (pour diminuer la consommation) et tant que des individus sont détectés, la lumière reste allumée et le confort sonore est indiqué. Le confort sonore est mesuré par l’ESP32-EYE grâce à un micro intégré qui relèvera l’intensité sonore. Si il est trop haut la LED clignotera pour avertir les personnes présentes. A noter qu'ici la LED n’est pas très voyante mais on pourra par la suite en ajouter une externe qui sera plus voyante. Lorsque plus personne n’est détectée, la caméra et la lumière s’éteignent et le capteur de présence reprend sa détection. 
L’avantage d’une caméra avec détection d’individus comparé à un détecteur de mouvement/présence est que même si la personne ne bouge pas, elle reste détectée. Qui ne s’est jamais retrouvé sans lumière aux toilettes et à du agiter les bras afin de voir quelque chose ?
Notre modèle embarquera 3 mods différents.
Le mode de fonctionnement normal fonctionne comme expliqué ci-dessus. Il affiche sur l’écran du terminal WIO le confort sonore lorsque des personnes sont détectées et fait clignoter la LED si l’intensité sonore est trop haute.
Le mode économie d’énergie n’utilisera pas l’écran afin de consommer moins de ressources. La LED clignotera toujours si l’intensité sonore est trop haute et embarquera une fonctionnalité supplémentaire. Cette dernière est l’utilisation d’un détecteur de luminosité au dos du terminal. Si on choisit de fixer le terminal sur une fenêtre, on pourra détecter si la lumière du soleil est assez forte et dans le cas échéant il ne sera pas nécessaire d’allumer la lumière.
Enfin le mode débogage affichera plus d'informations sur l’écran si on a besoin de vérifier le fonctionnement des différents capteurs et fera clignoter la LED.


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



