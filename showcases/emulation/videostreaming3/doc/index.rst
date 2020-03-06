Using Real Applications in a Simulated Network
==============================================

Goals
-----

In this showcase, we'll use real applications which communicate over a simulated network.
This feature is useful for testing real applications work over the network, without having to set up a real network. The simulated network can be easily configured for various topologies and behaviors to test a variety of cases.

We'll use INET's emulation features to interface the real world (the host OS environment) with the simulation.
INET has various modules which facilitate this interfacing, read about them in the Emulation section of the showcases page TODO link
In this particular scenario, we'll use a real video application to stream video to another real video application.

.. In the simulation scenario, a VLC instance streams video via the simulated network to another VLC instance.

Note that this showcase requires the ``Emulation`` feature of the INET Framework to be turned on (it's off by default), and it only runs on Linux.

| INET version: ``4.2``
| Source files location: `inet/showcases/emulation/videostreaming <https://github.com/inet-framework/inet-showcases/tree/master/emulation/TODO>`__

The Model
---------

The simulation scenario is illustrated with the following topological/theoretical/? schematic:

**TODO** meaning that this is the logical overview of the setup; which parts are simulated which are real and how they are interfaced is another layer on top of this; there are multiple ways to do that, e.g. at the link layer, or transport layer, etc. Actually, this layer is another layer on this schematic as well (blue).

so

- first, about the overview
- then, about where/how it is separated/interfaced
- emphasize other possibilities of separation/interfacing (other ext interfaces)
- then how that will work/the details of the scenario (?) -> the actual schematic
- the scripts
- the NED network
- the config
- maybe not in that order

.. The following schematic gives a logical overview of the simulation scenario:

.. figure:: media/setup.png
   :width: 50%
   :align: center

**V1** In the scenario, there are two hosts, a sender and a receiver. The hosts are realized in the real world from the link-layer up. Below that, the hosts and the network are simulated. The simulation and the real world is connected at the Ethernet interface. We'll use an :ned:`ExtUpperEthernet` interface. The upper part of this module is a TAP interface in the host OS, the lower part connects to the simulation. Packets received by the interface from the lower layers pass through the TAP interface to the host os. Inversely, packets received by the TAP interface are injected into the simulation.

**V2** In this scenario, a VLC instance in a sender host streams a video file to another VLC instance in a receiver host over the network. The hosts from the link-layer up are real, parts of the link-layer and the physical layer, and the network as well, are simulated.

**V2** We'll use the :ned:`ExtUpperEthernet` interface to separate the real and simulated parts of scenario.

**V1** The lower part of this interface is present in the simulation, and uses TAP interfaces in the host OS to send and receive packets to and from the upper layers of the host OS.

.. **TODO?**

**V2** The lower part of this interface is present in the simulation, and uses TAP interfaces in the host os to connect the host os and the simulation.

**V3** The lower part of this interface is present in the simulation, and uses TAP interfaces in the host OS to connect the host OS and the simulation, i.e. send and receive packets to and from the upper layers of the host OS.

Note that the real and simulated parts can be separated at other levels of the protocol stack, using other, suitable EXT interface modules, such as **TODO**.

**V1** Note that the in reality, the real parts of the sender and receiver hosts are the same machine, as both use the protocol stack of the host OS:

**V2** In reality, the real parts of the sender and receiver hosts are the same machine, as both use the protocol stack of the host OS:
**TODO** even though logically they are different hosts (they can actaully be on different machines TODO)

TODO

We'll use a VLC instance in the sender host to stream a video file. The packets travel down the host os protocol stack and enter the simulation at the Ethernet interface. Then they traverse the simulated network, enter the receiver host's Ethernet interface, and are injected into the host os protocol stack, and travel up to another VLC instance which plays the video.

The network for the simulation is the following:

.. figure:: media/Network.png
   :width: 80%
   :align: center

It contains two :ned:`StandardHost`'s, which are connected by switches (:ned:`EtherSwitch`) to a :ned:`Router`. The hosts are present in the simulation, and contain an :ned:`ExtUpperEthernetInterface`,
they are also present in the host OS.

.. The hosts contain an extupperethernet interface...

TODO sim time limit

Here is the configuration in omnetpp.ini:

.. literalinclude:: ../omnetpp.ini
   :language: ini

- the hosts use extupperethernetinterface
- need the scheduler class
- and the crc mode
- need to specify the tap interface (created by scripts; later)
- copy from the ext -> set the ip addresses from the script, and copy from there so they match
- set up NAT
- and ip addresses in the network
- cos we'll use that to send the video file -> its needed so that the packets get into the simulation/simulated network
