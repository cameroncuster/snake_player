import matplotlib
import tkinter as tk
import matplotlib.pyplot as plt

# instantiate scores
minScores = []
avgScores = []
maxScores = []

# read scores
for i in range( 0, 18 ):
    minScore = float( input( ) )
    avgScore = float( input( ) )
    maxScore = float( input( ) )
    minScores.append( minScore )
    avgScores.append( avgScore )
    maxScores.append( maxScore )

# board dimensions
boardSize = [
        "03x40", "03x40OB", "03x50", "03x50OB", "05x05", "05x05OB",
        "10x10", "10x10OB", "10x20", "10x20OB", "10x30", "10x30OB",
        "20x20", "20x20OB", "20x30", "20x30OB", "30x30", "30x30OB"
        ]

# plot the players
plt.plot( boardSize, maxScores, label='max',color='blue', marker='o' )
plt.plot( boardSize, avgScores, label='average',color='green', marker='o' )
plt.plot( boardSize, minScores, label='min',color='red', marker='o' )

# label the plot
plt.title( "Score Vs Board Dimensions" )
plt.xlabel( "Board Dimensions" )
plt.ylabel( "Score" )

# plot
plt.grid( True )
plt.legend( )
plt.show( )
