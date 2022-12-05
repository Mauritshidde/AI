from keras.datasets import mnist
from matplotlib import pyplot
 
#loading
(train_X, train_y), (test_X, test_y) = mnist.load_data()
 
#shape of dataset
print('X_train: ' + str(train_X.shape))
print('Y_train: ' + str(train_y.shape))
print('X_test:  '  + str(test_X.shape))
print('Y_test:  '  + str(test_y.shape))
 
#plotting
print(train_X[0][0])

import json
dataset = {}
rowarray_list = []
images = {}
for i in range(10000):
    # image = {
    #     'pixels': {
    #         },
    #     'answer': train_y[i],
    #     }
    # xz = {row[0]}
    # contact_mogelijkheden.update(xz)
    # for i in range()
    # imagepixels = train_X[0][0][i]
    # image.update(imagepixels)
    # dataset.update(image)
    image = {}
    colums = {}
    for j in range(28):
        rows = {}
        for k in range(28):
            value = train_X[i][j][k]/255
            row = {
                k:value
            }
            rows.update(row)
        column = {
            j:rows
        }
        colums.update(column)
    image = {
        i:{
            "data":colums,
            "value":int(train_y[i])
        }
    }
    images.update(image)
# string_data = json.dumps(data, separators=(',', ':'))
print(images[0]["data"][0], train_y[0])
with open("MNIST.json", "w") as write_file:
    json.dump(images, write_file, separators=(',', ':'))
with open("MNIST.json", "r") as read_file:
    print(read_file.read())

            
# from matplotlib import pyplot
# for i in range(9):  
#     pyplot.subplot(330 + 1 + i)
#     pyplot.imshow(train_X[i], cmap=pyplot.get_cmap('gray'))
#     pyplot.show()
    