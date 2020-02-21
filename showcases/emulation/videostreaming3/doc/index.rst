Using Real Applications in a Simulated Network
==============================================

Goals
-----

In this showcase, we'll use real applications which communicate over a simulated network.
This feature is useful for testing real applications work over the network, without having to set up a real network. The simulated network can be easily configured for various topologies and behaviors to test a variety of cases.

We'll use INET's emulation features to interface the real world (the host OS environment) with the simulation.
INET has various modules which facilitate this interfacing, read about them in the Emulation section of the showcases page TODO link
In this particular scenario, we'll use a real application to stream video to another real video application.

.. In the simulation scenario, a VLC instance streams video via the simulated network to another VLC instance.

Note that this showcase requires the ``Emulation`` feature of the INET Framework to be turned on (it's off by default), and it only runs on Linux.

| INET version: ``4.2``
| Source files location: `inet/showcases/emulation/videostreaming <https://github.com/inet-framework/inet-showcases/tree/master/emulation/TODO>`__

The Model
---------

The simulation scenario is illustrated with the following schematic:

The following schematic gives a logical overview of the simulation scenario:

.. figure:: media/setup.png
   :width: 50%
   :align: center

In the scenario, there are two hosts, a sender and a receiver. The hosts are realized in the real world from the link-layer up. Below that, the hosts and the network are simulated. The simulation and the real world is connected at the Ethernet interface. We'll use an :ned:`ExtUpperEthernet` interface. The upper part of this module is a TAP interface in the host OS, the lower part connects to the simulation. Packets received by the interface from the lower layers pass through the TAP interface to the host os. Inversely, packets received by the TAP interface are injected into the simulation.

We'll use a VLC instance in the sender host to stream a video file. The packets travel down the host os protocol stack and enter the simulation at the Ethernet interface. Then they traverse the simulated network, enter the receiver host's Ethernet interface, and are injected into the host os protocol stack, and travel up to another VLC instance which plays the video.

The network for the simulation is the following:

.. figure:: media/Network.png
   :width: 80%
   :align: center

It contains two :ned:`StandardHost`'s, which are connected by switches (:ned:`EtherSwitch`) to a :ned:`Router`. The hosts contain an extupperethernet interface...