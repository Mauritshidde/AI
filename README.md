# AI learns to drive
AI for the AI learns to drive specilisation
this project has 3 types of  AI.
1. deep neuralnetwork
2. genetic AI
3. Qtable

## information

### map drawer

the map drawer uses key inputs to switch drawing mode 
#### key bindings:
```
O: innerwall drawing mode  

P: outerwall drawing mode

Q: car spawnpoint placements 

C: checkpoint placement

X: select checkpoint

Enter: save map to example.json

Left SHift: conform car palcement

Left mouse button: add coordinate/sellect line

Right mouse button: remove last coordinate/line
```


the 'X' mode lets you select an checkpoint you can't unsellect this and this is the firscheckpoint the car should reach. 
If there are 2 cars and you pressed one checkpoint with this is the first checkpoint that the first car should reach and you need to click another checkpoint for the other line.

for every car placed you should click a checkpoint using the 'X' mode. If you do not do this and press 'Enter' to save the map 
the program will crash and not save the map.

### neuralnetwork visualisation

the red circles in the visualisation are the neurons that have an output value that is greater than 0.5.
And the red lines are weights that have an negative value

### map GeneticAI

In the map GeneticAI is the newest and best code for the drawing of the ai learning visualisation.
The car learns by chosing the best car and mutating it using the a mutationRate and the lerp function.
The neuralnetwork uses relu and is savable.
Saving a neuralnetwork wil update the file GNN.json and loading an neuralnetwork will use NN.json.
The car uses the first spawnlocation in the map file.
The window of Genetic shows some data in the top left corner and has a small cirlce that lets you draw a cube to replace the location of 
the neuralnetwork visualisation.

### map DeepNN
#### key binds:
```
Left ctrl: save neuralnetwork to NN.json

Right ctrl: load the neuralnetwork from NN.json
```
In the map DeepNN the window is rescalable, (but the rays won't scale down with it) and it uses backpropagation
to update weights and biases in the neuralnetwork to improve the actions that the car takes.

The DeepNN car uses the multiple spawn locations on the map to train the ai while the geneticAi uses only 1 fixed spawn location.

### map QtableAI

This car uses older code for the map loading, drawing and car. And uses an Qtable to take the best possible descision.
This car can uses the multiple spawnpoints of the map.


## Instalation guide linux:

### using make(only option):
```
git clone https://github.com/Mauritshidde/AI.git AI
cd AI
make
```
#### to run the script type:
```
./main
```


