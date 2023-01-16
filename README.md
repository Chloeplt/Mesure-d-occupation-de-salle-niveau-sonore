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

- Pour les salles de réunions des entreprises 

- Pour les bibliothèques

- Pour les supermarchées 

- Pour les salle de concert, bar, salle de sport ect



![alt text](https://github.com/Chloeplt/Mesure-d-occupation-de-salle-niveau-sonore/blob/main/img/exemple_d'utilisation_projet_iot.png?raw=true)

### Voci la brochure commercial de notre produit :
#### L'exterieur de la brochure 
![alt text](https://github.com/Chloeplt/Mesure-d-occupation-de-salle-niveau-sonore/blob/main/img/exte_brochure.jpg?raw=true)
#### L'interieure de la brochure 
![alt text](https://github.com/Chloeplt/Mesure-d-occupation-de-salle-niveau-sonore/blob/main/img/inte_brochure.jpg?raw=true)

Une vidéo de démonstration est disponible ici.

## Analyse de marché - Chloé
> Consigne : rechercher et analyser (avantages/inconvénients sous la forme d’une grille) des produits concurrents
> Consigne : réaliser une analyse (rapide) du marché des produits commerciaux concurrents

- Notr
## Architechture globale du système - Léo
> Consigne : définir l’architecture globale du systèmes (ensemble d’objets, service en ligne (cloud))

 Le système est composé d’un WIO Terminal, d’un ESP32-EYE et d’un capteur de présence PIR. 
 L’ESP32-EYE est un capteur embarquant une caméra et un microphone. Il communiquera avec le Wio Terminal grâce au protocole Wifi. Le capteur PIR sera utilisé pour détecter la présence de quelqu’un et communiquera directement avec le Wio Terminal sur lequel il sera branché. Enfin nous utiliserons des éléments directement présent sur le Wio Terminal tel qu’une LED, les boutons pour avoir plusieurs mods de fonctionnement (mode normal, mode économie d'énergie, mode débogage), ainsi que l’écran d’affichage si besoin, cela dépendra de l’autonomie souhaité et du mode en cours d’utilisation. Pour le mode normal il sera possible d’afficher des données en temps réel et l’écran pourra être utile pour le mode débogage car on pourra afficher plus de variables.
Le principe de fonctionnement est le suivant. Lorsque le capteur de présence PIR détecte un mouvement, il allume la caméra et la lumière. Cette dernière est ici représentée par la LED du Wio Terminal. La caméra (embarqué sur l’ESP32-EYE) prend alors le relais pour détecter la présence d’individus. Elle prend une photo toutes les minutes (pour diminuer la consommation) et tant que des individus sont détectés, elle transmet au terminal WIO le taux d’occupation de la pièce. Tant qu’il y a détection, la lumière reste allumée et le confort sonore ainsi que le taux d’occupation de la pièce est indiqué. Le confort sonore est mesuré par l’ESP32-EYE grâce à un micro intégré qui relèvera l’intensité sonore. Si il est trop haut la LED clignotera pour avertir les personnes présentes. A noter qu'ici la LED n’est pas très voyante mais on pourra par la suite en ajouter une externe qui sera plus voyante. Lorsque plus personne n’est détectée, la caméra et la lumière s’éteignent et le capteur de présence reprend sa détection. 
 L’avantage d’une caméra avec détection d’individus comparé à un détecteur de mouvement/présence est que même si la personne ne bouge pas, elle reste détectée. Qui ne s’est jamais retrouvé sans lumière aux toilettes et à du agiter les bras afin de voir quelque chose ?
Notre modèle embarquera 3 mods différents.
 Le mode de fonctionnement normal fonctionne comme expliqué ci-dessus. Il affiche sur l’écran du terminal WIO le confort sonore et le taux d’occupation lorsque des personnes sont détectées. Si fait clignoter la LED si l’intensité sonore est trop haute.
 Le mode économie d’énergie n’utilisera pas l’écran afin de consommer moins de ressources. La LED clignotera toujours si l’intensité sonore est trop haute et embarquera une fonctionnalité supplémentaire. Cette dernière est l’utilisation d’un détecteur de luminosité au dos du terminal. Si on choisit de fixer le terminal sur une fenêtre, on pourra détecter si la lumière du soleil est assez forte et dans le cas échéant il ne sera pas nécessaire d’allumer la lumière.
Enfin le mode débogage affichera plus d'informations sur l’écran si on a besoin de vérifier le fonctionnement des différents capteurs et fera clignoter la LED.
On pourra aussi définir un mode supplémentaire de surveillance, celui-ci serait actif en dehors des plages d’utilisations de la salle/pièce. Le fonctionnement serait similaire à celui du mode économie d’énergie mais si quelqu’un est détecté, la caméra prendra en photo l’individu toutes les 5 secondes et cette photo sera envoyée par wifi, on pourra se connecter avec un ordinateur au wifi pour récupérer ses différentes photos en temps réel.



## Sécurité globale - Chloé

Nous utilisons un protocole Wifi pour communiquer entre notre ESP-EYE et notre Wio Terminal. Afin d’assurer une sécurité optimale de notre système il faut :

-	Mettre en place une **clé de chiffrement de 256 bits**. Nous utilisons une clé de chiffrement très forte car les données transmissent sont très sensible, nous voulons donc maximiser la sécurité. Cette première étape permet de lutter contre les attaques de force brute.

-	Utiliser le **protocole de sécurité WPA2**(Wifi Protected Access) qui utilise un chiffrement AES(Advanced Encryption Standard), afin de lutter contre les attaques de type « meet in the middle ».

Un **SSID** et un **mot de passe** seront d’ores et déjà configuré dans le système et ne pourront être visible et modifiable qu’avec un mot de passe.


## Respect de la vie privée du service - Léo
> Consigne : définir le respect de la vie privée du service ([RGPD](https://www.cnil.fr/fr/reglement-europeen-protection-donnees)) : lister les risques d’atteinte au respect de la vie privée

Pour la **caméra**, le **micro** et le **capteur de détection PIR**, le principal risque d’atteinte au respect de la vie privée provient d’une possible déduction d’informations sur les activités et les habitudes de vie des personnes dans l'environnement **surveillé**. 

Cela pourrait survenir si quelqu’un parvient à **prendre le contrôle** ou à **récupérer les informations** des différents capteurs. Cependant les capteurs n’offrent pas les mêmes informations. Le capteur de présence sera limité à savoir les habitudes de présence dans l’environnement surveillé. Le micro est seulement utilisé pour **mesurer le volume sonore**, il peut donc fournir la même information que le capteur de présence. 

Cependant, si quelqu’un arrive à **flasher un autre code** par dessus, il pourrait avoir accès aux **conversations présentes dans la pièce**. Enfin la caméra pourra offrir une information supplémentaire à la présence ou non d’individus, celle de l’**image**. Une personne pourra donc potentiellement récupérer les photos envoyées par la caméra si il arrive à s’y connecter et changer le code ou alors si il parvient à **se connecter au wifi**, que la caméra est dans le mode surveillance et que quelqu’un est détecté (donc en dehors des horaires d’utilisation de la pièce/salle.

Des mesures peuvent être prises pour **avertir les utilisateurs** ou **diminuer les risques**. Le principal moyen de diminuer les risques est de rajouter un **chiffrement des données** en plus de la **sécurité du Wifi**. Un autre moyen serait de rendre l’accès au dispositif plus dur. Par exemple en le **dissimulant**, en le disposant en hauteur ou en confectionnant un boîtier supplémentaire pour compliquer une connexion au hardware.

Pour la partie avertissement des utilisateurs, leur diffuser une **politique de confidentialité**, leur faire signer des **conditions d’utilisations** ou demander leur accords si le cadre est privé peuvent être une possibilité.


## Architecture matérielle de l'objet - Chloé
> Consigne : définir l’architecture matérielle de l’objet, -> voir si la partie Architechture globale du système ne répond pas à cette question

## Coût de la BOM du produit - Léo
> Consigne : 
> estimer le coût de la BOM de votre produit (composants, PCB et enclosure) pour 5000 unités produites
. pour le boitier, vous pouvez rechercher des boitiers “standards” disponibles dans les catalogues fournisseurs
. pour le PCB, vous pouvez fournir une estimation du prix de fabrication du PCB et du masque chez des fournisseurs comme [https://jlcpcb.com/](https://jlcpcb.com/) , [https://www.wedirekt.fr/fr/](https://www.wedirekt.fr/fr/) …

| Matériel        | Quantité | Prix unitaire      | Prix total       |
|-----------------|----------|--------------------|------------------|
| Wio Terminal    | 1        | 30,9               | 154500           |
| PIR motion sensor| 1       | 6,1                | 30500            |
| ESP32-EYE       | 1        | 22,5               | 112500           |
| LED             | 1        | 0,0447             | 223,5            |
| Système complet | 5000     | 59,5447            | 297723,5         |


Note : les prix indiqués sont en *$*


## Coût de certification ETSI du produit - Chloé

Le cout de la certification ETSI dépend principalement des normes ETSI appliqué à notre produit. Mais il est assez difficile d’avoir une idée précise du prix. En effet, le cout dépend aussi de nombreux autres facteurs tels que la complexité du produit, le nombre de tests requis et les coûts administratifs associés à la certification. 

Le Wio terminal utilise des bandes passantes de fréquences 2.4 GHz, nous pouvons donc en déduire certaine norme applicable à notre produit :

-	**EN 300 328:** Cette norme spécifie les exigences pour l'utilisation des bandes de fréquences de 2,4 GHz pour les dispositifs sans fil dans l'Union Européenne. Cette norme couvre les exigences de compatibilité électromagnétique (CEM) et de sécurité pour les dispositifs sans fil utilisant ces bandes de fréquences.
-	
-	**EN 301 489-1:** Cette norme spécifie les exigences pour l'immunité électromagnétique pour les équipements terminaux et les équipements réseau utilisés dans les systèmes de communication électronique.
-	
-	**EN 301 489-17:** Cette norme spécifie les exigences pour la sécurité des équipements terminaux et des réseaux utilisés dans les systèmes de communication électronique.
-	
-	**EN 303 645:** Cette norme spécifie les exigences de sécurité pour les objets connectés (smart-objects) utilisant les technologies de communication radio. 

Les certifications coutent en moyenne 800€ pour 3 ans de validité. On peut donc estimer un **total de 1067€/ans.**


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



