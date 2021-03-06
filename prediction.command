#!/bin/bash

app_path="prediction/"     
cd $app_path

echo "Début de la prédiction"
python2 -m scripts.label_image_osc \
    --graph=tf_files/retrained_graph.pb\
    --image=tf_files/images.duckduckgo.png
echo "Fin de la prédiction"
exit 0


python2 -m scripts/label_image_osc.py \
--graph=tf_files/retrained_graph.pb\
--image=tf_files/images.duckduckgo.png
