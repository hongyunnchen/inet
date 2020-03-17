package inet.showcases.wireless.analogmodel;

import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.node.inet.AdhocHost;
import inet.node.inet.ManetRouter;
import inet.node.inet.WirelessHost;
import inet.physicallayer.common.packetlevel.NoiseSource;
import inet.physicallayer.ieee80211.packetlevel.Ieee80211DimensionalRadioMedium;
import inet.physicallayer.unitdisk.UnitDiskRadioMedium;
import inet.visualizer.integrated.IntegratedMultiVisualizer;
import inet.visualizer.integrated.IntegratedVisualizer;


network AnalogModelShowcaseRoutingNetwork
{
    int numHosts;
    @display("bgb=400,400");
    submodules:
        configurator: Ipv4NetworkConfigurator {
            @display("p=35,40");
        }
        radioMedium: UnitDiskRadioMedium {
            @display("p=32,113");
        }
        visualizer: IntegratedVisualizer {
            @display("p=37,185");
        }
        host[numHosts]: AdhocHost;
}

network AnalogModelShowcaseRoutingNetwork2
{
    parameters:
        @display("bgb=400,400");
        int numHosts;
    submodules:
        sourceHost: ManetRouter;
        host[numHosts]: ManetRouter;
        destinationHost: ManetRouter;
        radioMedium: UnitDiskRadioMedium {
            @display("p=38,28");
        }
        configurator: Ipv4NetworkConfigurator {
            @display("p=38.461544,66.863914");
        }
        visualizer: IntegratedMultiVisualizer {
            @display("p=38.461544,106.50889");
        }
}

network AnalogModelShowcaseRoutingNetwork3
{
    parameters:
        @display("bgb=400,400");

    submodules:
        source: ManetRouter {
            @display("p=104,335");
        }
        node1: ManetRouter {
            @display("p=104,226");
        }
        node2: ManetRouter {
            @display("p=175,140");
        }
        node3: ManetRouter {
            @display("p=238,276");
        }
        node4: ManetRouter {
            @display("p=312,196");
        }
        node6: ManetRouter {
            @display("p=147,67");
        }
        node7: ManetRouter {
            @display("p=60,125");
        }
        destination: ManetRouter {
            @display("p=292,80");
        }
        radioMedium: UnitDiskRadioMedium {
            @display("p=38,28");
        }
        configurator: Ipv4NetworkConfigurator {
            @display("p=38.461544,66.863914");
        }
        visualizer: IntegratedMultiVisualizer {
            @display("p=38.461544,106.50889");
        }
}

network AnalogModelShowcaseNoiseNetwork
{
    @display("bgb=400,400");
    submodules:

        configurator: Ipv4NetworkConfigurator {
            @display("p=35,40");
        }
        radioMedium: Ieee80211DimensionalRadioMedium {
            @display("p=32,113");
        }
        visualizer: IntegratedVisualizer {
            @display("p=37,185");
        }
        host1: AdhocHost {
            @display("p=196,83");
        }
        host2: AdhocHost {
            @display("p=157,158");
        }
        host3: AdhocHost {
            @display("p=251,255");
        }
        host4: AdhocHost {
            @display("p=311,270");
        }
        noiseSource: NoiseSource {
            @display("p=307,133");
        }
}
