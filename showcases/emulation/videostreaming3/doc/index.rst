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

The Simulation Setup
--------------------

structure

- briefly about the emulation support? or not
- the setup
- the network
- the extethernet
- the scripts
- the configs

.. figure:: media/setup.png
   :width: 50%
   :align: center

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
