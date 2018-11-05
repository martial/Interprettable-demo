#!/bin/bash

app_path="/Users/erasme/Desktop/interpretabble/Translations/prediction"     
cd $app_path

echo "Début de la prédiction"
python2 -m scripts.label_image_osc \
    --graph=tf_files/retrained_graph.pb  \
    --image=tf_files/images.duckduckgo.jpg
echo "Fin de la prédiction"
exit 0