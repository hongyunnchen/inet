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

We'll use the :ned:`ExtUpperEthernet` interface to connect the real and simulated parts of scenario.
The lower part of this interface is present in the simulation, and uses TAP interfaces in the host OS to send and receive packets to and from the upper layers of the host OS.

.. **V2.2** The lower part of this interface is present in the simulation, and uses TAP interfaces in the host os to connect the host os and the simulation.

.. **V2.3** The lower part of this interface is present in the simulation, and uses TAP interfaces in the host OS to connect the host OS and the simulation, i.e. send and receive packets to and from the upper layers of the host OS.

Note that the real and simulated parts can be separated at other levels of the protocol stack, using other, suitable EXT interface modules, such as **TODO**.

.. **V1** Note that the in reality, the real parts of the sender and receiver hosts are the same machine, as both use the protocol stack of the host OS:

In reality, the real parts of the sender and receiver hosts are the same machine, as both use the protocol stack of the host OS:
**TODO** even though logically they are different hosts (they can actaully be on different machines TODO)

TODO

We'll use a VLC instance in the sender host to stream a video file. The packets travel down the host os protocol stack and enter the simulation at the Ethernet interface. Then they traverse the simulated network, enter the receiver host's Ethernet interface, and are injected into the host os protocol stack, and travel up to another VLC instance which plays the video.

The network for the simulation is the following:

.. figure:: media/Network.png
   :width: 80%
   :align: center

.. figure:: media/Network2.png
   :width: 80%
   :align: center

It contains two :ned:`StandardHost`'s, which are connected by switches (:ned:`EtherSwitch`) to a :ned:`Router`.

  The hosts contain an :ned:`ExtUpperEthernetInterface`,
  they are also present in the host OS.

- the vlc sender will send the video stream to the address out the router
- the router will perform NAT to the address of the TAP interface of the receiver host
- this is required so that the packets enter the simulation
- otherwise they would use the loopback interface

- the configuration
- the scripts start the simulation and the streaming

The sender application will stream the video to the address of the router in the simulation.
The router will perform network address translation to rewrite the destination address to the address of the receiver host's Ext/Tap interface.

**V1** This is required so that the video packets enter the simulated network; if they were sent to the receiver host's ext/tap interface, they would go through the loopback interface.

**V2** This is required so that the video packets enter the simulation, instead of going through the loopback interface.

Three shell scripts in the showcase's directory can be used to control the emulation scenario.
The ``setup.sh`` script creates the tap interfaces, assigns IP addresses to them, and brings them up:

.. literalinclude:: ../setup.sh
   :language: bash

The ``teardown.sh`` script does the opposite; it destroys the tap interfaces after the user is done playing with this whole thing TODO.

.. literalinclude:: ../teardown.sh
   :language: bash

The ``run.sh`` script starts the simulation, and both video applications:

.. literalinclude:: ../run.sh
   :language: bash

.. The hosts contain an extupperethernet interface...

**TODO** sim time limit

Here is the configuration in omnetpp.ini:

.. literalinclude:: ../omnetpp.ini
   :language: ini

In the configuration, the scheduler class is set to ``RealTimeScheduler`` so that the simulation can run in the real time of the host OS.
The hosts are configured to have an :ned:`ExtUpperEthernetInterface`, and to use the TAP devices which were created by the setup script. The script assigned IP addresses to the TAP interfaces; the tap interfaces are set to copy the addresses from the tap interfaces.
Finally, the addresses in the network are important; the configurator is set to assign the correct addresses so the simulation and the script can work together (the VLC sends the video packets to the router, so its address needs to match as the destination address in the script).
The NAT table in the router's ivp4 module is configured to rewrite the source and destination address
of packets which are addressed to it's eth0 interface before routing; the resulting packets have a source address of the router's eth1 interface and the destination address of the receiver host's ext interface. **TODO** rewrite
Also, need to calculate CRC/FCS to properly serialize/deserialize packets

- the hosts use extupperethernetinterface
- need the scheduler class
- and the crc mode
- need to specify the tap interface (created by scripts; later)
- copy from the ext -> set the ip addresses from the script, and copy from there so they match
- set up NAT
- and ip addresses in the network
- cos we'll use that to send the video file -> its needed so that the packets get into the simulation/simulated network
