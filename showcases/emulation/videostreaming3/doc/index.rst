Using Real Applications in a Simulated Network
==============================================

Goals
-----

In this showcase, we'll use real applications which communicate over a simulated network.
This feature is useful for testing real applications work over the network, without having to set up a real network. The simulated network can be easily configured for various topologies and behaviors to test a variety of cases.

.. TODO

   so

   a vlc instance is streaming video through the simulated network to another vlc which receives the stream

In the simulation scenario, a VLC instance streams video via the simulated network to another VLC instance.

Note that this showcase requires the ``VoIPStream`` and ``Emulation`` features of the INET Framework to be turned on (they are off by default), and it only runs on Linux.

| INET version: ``4.2``
| Source files location: `inet/showcases/emulation/videostreaming <https://github.com/inet-framework/inet-showcases/tree/master/emulation/TODO>`__

...

.. The Simulation Setup
   --------------------

The Model
---------

   structure

   - briefly about the emulation support? or not
   - the setup
   - the network
   - the extethernet
   - the scripts
   - the configs

Here is the schematic of the simulation setup:

.. figure:: media/setup.png
   :width: 50%
   :align: center

TODO there are two hosts; 

   In the scenario, there is a sender host and a receiver host. A VLC instance in the sender host streams a video file over the simulated network to another VLC instance in the receiver host. 
   The simulation and the real world (the host OS environment) is separated at the Ethernet interface in the hosts. 

.. this is the logical overview. In the logical schematic there are two hosts

There are two hosts in this scenario, a sender and a receiver. Some part of the scenario is realized in the real world (the host OS environment), the other is simulated. The simulated and the real world is separated at the Ethernet interface in each host. Thus the hosts from the Link-layer up are real, and the other parts are simulated.

so

actually

- the hosts are mostly real
- this is the logical schematic

TODO its actually just one UDP and IP because its the host os protocol stack

so

.. code-block:: text
   :caption: Actually its the specific schematic, not the logical one; in that, there are two hosts, but both are realized by the host os

   VLC       VLC
   |         |
   ----| |----
       UDP
        |
       IP
        |
    ----------
    |        |       real
   ext      ext      ----
    |        |       sim
   ------------
   | network  |
   ------------

In the setup, a real VLC instance streams a video file. The packets will traverse a simulated network to another VLC instance which plays the video. Here is the network:

.. TODO network

.. figure:: media/Network.png
   :width: 80%
   :align: center

TODO extEthernet

   so

   - this showcase is about running real applications in a simulated network
   - this is useful to test applications without having to build a real network
   - its more flexible that way
   - the scenario is that a VLC media player instance streams a video file over a simulated network to another instance, which plays it
   - the simulated and real parts are separated at the phy/link layer
   - we'll use ExtUpperEthernet interface to do that
   - the host os will have a two tap devices each associated to an extupperethernet interface
   - and packets will be created by VLC, and sent down the protocol stack (UDP, IP) and into the tap device
   - which sends it into the simulation
   - it traverses the network and up the protocol stack to the other VLC

   - the network contains a router and two etherswitches
   - but it could be any arbitrary simulated network
