'''
Copyright (c) 2014-2015 Kartik Kumar, Dinamica Srl
Copyright (c) 2014-2015 Marko Jankovic, DFKI GmbH
Copyright (c) 2014-2015 Natalia Ortiz, University of Southampton
Copyright (c) 2014-2015 Juan Romero, University of Strathclyde
Distributed under the MIT License.
See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
All rights reserved.
'''

# Set up modules and packages
# Plotting
import matplotlib
matplotlib.use('TkAgg')
import matplotlib.pyplot as plt
# from matplotlib import rcParams
# from matplotlib import cm
from mpl_toolkits.mplot3d import Axes3D
from mpl_toolkits.mplot3d import axes3d

# I/O
import commentjson
import json
from pprint import pprint

# Numerical
import numpy as np
import pandas as pd

# System
import sys
import time

print ""
print "------------------------------------------------------------------"
print "                             Scarab                               "
print "        Simulator for close-range removal of Ariane bodies        "
print "                              0.0.1                               "
print "                     Copyright (c) 2014-2015                      "
print "------------------------------------------------------------------"
print ""

# Start timer.
start_time = time.time( )

print ""
print "******************************************************************"
print "                          Input parameters                        "
print "******************************************************************"
print ""

# Parse JSON configuration file
# Raise exception if wrong number of inputs are provided to script
if len(sys.argv) != 2:
    raise Exception("Only provide a JSON config file as input!")

json_data = open(sys.argv[1])
config = commentjson.load(json_data)
json_data.close()
pprint(config)

print ""
print "******************************************************************"
print "                            Operations                            "
print "******************************************************************"
print ""

# Read and store input files.
print "Input data files are being read ..."
metadata = pd.read_csv(config["metadata"], header=None)
metadata_table = []
metadata_table.append(["$\mu$",                  float(metadata[1][0]), "$km^3 s^{-2}$"])
metadata_table.append(["$x_{0}$",                float(metadata[1][1]), "$km$"])
metadata_table.append(["$y_{0}$",                float(metadata[1][2]), "$km$"])
metadata_table.append(["$z_{0}$",                float(metadata[1][3]), "$km$"])
metadata_table.append(["$Vx_{0}$",               float(metadata[1][4]), "$km s^{-1}$"])
metadata_table.append(["$Vy_{0}$",               float(metadata[1][5]), "$km s^{-1}$"])
metadata_table.append(["$Vz_{0}$",               float(metadata[1][6]), "$km s^{-1}$"])
metadata_table.append(["$t_{0}$",                float(metadata[1][7]), "$s$"])
metadata_table.append(["$t_{f}$",                float(metadata[1][8]), "$s$"])
metadata_table.append(["$\Delta t_{0}$",         float(metadata[1][9]), "$s$"])
state_history = pd.read_csv(config['state_history'])
print "Input data files successfully read!"

print "Figure being generated ..."

# Generate figure with 2D views
fig = plt.figure()
ax1 = fig.add_subplot(2, 2, 1)
ax2 = fig.add_subplot(2, 2, 2)
ax3 = fig.add_subplot(2, 2, 3)
ax4 = fig.add_subplot(2, 2, 4, frameon=False)

# Plot X-Y projection
ax1.plot(0.0,0.0,'ob')
ax1.plot(state_history['x'],state_history['y'],color='k')
ax1.set_xlabel('x [km]')
ax1.set_ylabel('y [km]')
ax1.ticklabel_format(style='sci', axis='both', scilimits=(0,0))
ax1.grid()

# Plot X-Z projection
ax2.plot(0.0,0.0,'ob')
ax2.plot(state_history['x'],state_history['z'],color='k')
ax2.set_xlabel('x [km]')
ax2.set_ylabel('z [km]')
ax2.ticklabel_format(style='sci', axis='both', scilimits=(0,0))
ax2.grid()

# Plot Y-Z projection
ax3.plot(0.0,0.0,'ob')
ax3.plot(state_history['y'],state_history['z'],color='k')
ax3.set_xlabel('y [km]')
ax3.set_ylabel('z [km]')
ax3.ticklabel_format(style='sci', axis='both', scilimits=(0,0))
ax3.grid()

# Plot metadata table
ax4.axis('off')
the_table = ax4.table(cellText=metadata_table,colLabels=None,cellLoc='center',loc='center')
the_table.auto_set_font_size(False)
the_table.set_fontsize(10)
table_props = the_table.properties()
table_cells = table_props['child_artists']
for cell in table_cells: cell.set_height(0.1)
cell_dict = the_table.get_celld()
for row in xrange(0,len(metadata_table)): cell_dict[(row,2)].set_width(0.2)

# Save figure
plt.tight_layout()
plt.savefig(config["figure"], dpi=config["figure_dpi"])

# Generate 3D figure if requested.
if config["show_3D_figure"]:
    fig = plt.figure()
    ax = fig.gca(projection='3d')
    ax.set_xlabel('x [km]')
    ax.set_ylabel('y [km]')
    ax.set_zlabel('z [km]')
    ax.ticklabel_format(style='sci', axis='both', scilimits=(0,0))

    # Plot sphere for the Earth
    radius_Earth = 6371.0 # km
    u = np.linspace(0, 2 * np.pi, 100)
    v = np.linspace(0, np.pi, 100)
    x = radius_Earth * np.outer(np.cos(u), np.sin(v))
    y = radius_Earth * np.outer(np.sin(u), np.sin(v))
    z = radius_Earth * np.outer(np.ones(np.size(u)), np.cos(v))
    ax.plot_surface(x, y, z,  rstride=4, cstride=4, color='b',edgecolors='b')

    # Plot orbit.
    ax.plot3D(state_history['x'],state_history['y'],state_history['z'],'k')

    # Create cubic bounding box to simulate equal aspect ratio
    X = state_history['x']
    Y = state_history['y']
    Z = state_history['z']
    max_range = np.array([X.max()-X.min(), Y.max()-Y.min(), Z.max()-Z.min()]).max() / 2.0
    mean_x = X.mean()
    mean_y = Y.mean()
    mean_z = Z.mean()
    ax.set_xlim(mean_x - max_range, mean_x + max_range)
    ax.set_ylim(mean_y - max_range, mean_y + max_range)
    ax.set_zlim(mean_z - max_range, mean_z + max_range)

    plt.grid()
    plt.show()

print "Figures generated successfully!"
print ""

# Stop timer
end_time = time.time( )

# Print elapsed time
print "Script time: " + str("{:,g}".format(end_time - start_time)) + "s"

print ""
print "------------------------------------------------------------------"
print "                         Exited successfully!                     "
print "------------------------------------------------------------------"
print ""
