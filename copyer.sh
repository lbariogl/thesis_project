#!/bin/bash

#Questo script copia le bacro da thesis_project alla cartella corrente

cp $HOME/thesis_project/MinimTopology.* . || printf "Failed to copy MinimTopology.*\n"
cp $HOME/thesis_project/Dictionary.* . || printf "Failed to copy Dictionary.*\n"
cp $HOME/thesis_project/BuildDictionary.* . || printf "Failed to copy BuildDictionary.*\n"
cp $HOME/thesis_project/LookUp.* . || printf "Failed to copy Lookup.*\n"
cp $HOME/thesis_project/FastSimulation.* . || printf "Failed to copy FastSimulation.*\n"
cp $HOME/thesis_project/testBuild.C . || printf "Faild to copy testBuild.C\n"
cp $HOME/thesis_project/compiler.C . || printf "Failed to copy compiler.C\n"
cp $HOME/thesis_project/testSimulation.C .|| printf "Failed to copy testSimulation.C\n"
cp $HOME/thesis_project/testLookUp.C .|| printf "Failed to copy testLookup.C\n"
cp $HOME/thesis_project/HistoFiller.C .|| printf "Failed to copy HistoFiller.C\n"
