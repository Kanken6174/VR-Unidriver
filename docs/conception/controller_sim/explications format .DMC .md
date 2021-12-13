# Explication du format DMC
Le format DMC utilisé par le projet domocap sert à configurer des drivers dynamiquement selon les valeurs spécifiées dedans.

Ce fichier est lu à la fois par le driver et la moulinette et sert de "contrat" sur quelles données à échanger, sous quel
format et ce qu'elles signifient.

exemple de format DMC:
```yaml
#on donne le nom du driver, cela en créé un nouveau à chaque $
$mess
#on donne le modèle 3d à utiliser pour le driver
>oculus_cv1_controller_right
#on définit le rôle du driver (1 = main gauche, 2 = droite, 3 = pas applicable,...)
<2
#on définit désormais les composants de ce driver
#   on donne d'abord son chemin d'action
=/input/a/click
#   puis son type (0-5 = type openVR digital, analogique, entrée squelette...; 5+ = touche de clavier à surveiller mode booléen)
:78
#   et enfin sa lettre de délimitation dans la trame, utilisé non pas par le driver mais par la moulinette
~J
=/input/b/click
:72
~K
=/input/system/click
:74
~L
=/input/x/click
:75
~M
=/pose/mag/x
:1
~A
=/pose/mag/y
:99
~B
@file loaded
```

## opérateurs

`$` définit le nom d'un nouvel appareil (nouveau "driver" dans le driver, nouvel appareil à connecter sur un port série).
`>` donne le modèle 3d à utiliser pour cet appareil (partie driver uniquement).
`<` définit l'indice de role du driver, `0` pour non applicable, `1` pour main gauche, `2` pour main droite (openVR uniquement)
`=` définit un nouveau chemin d'action steamVR et correspond à un nouveau composant d'un appareil (bouton, joystick...),
il faut noter que cela est lu de 2 façon différentes, le driver créé un nouveau composant pour un appareil si il commence
par /input car il ne reconnait pas les /pose, qui sont eux lus par la moulinette, pour définir les composants liés à la
position de l'appareil (la moulinette lit à la fois les /input et /pose).
`:` définit le type de composant (0-5) ou la touche de clavier à surveiller (5+) en mode simulation clavier
`~` définit la lettre qui correspond à la valeur de ce composant dans la trame sérial de l'appareil (index A-Z), ignoré par le driver,
uniquement lu par la moulinette
`@` est un commentaire "bruyant", il sera affiché dans le log de steamVR.
`#` et n'importe quel autre symbole correspond à un commentaire, et sera ignoré par le driver et la moulinette.