UEs = 900:30:48000;
plot(UEs,throughput(3,:),'r');
hold on;
plot(UEs,throughput(6,:),'b');
hold on;
plot(UEs,throughput(9,:),'m');
hold on;
plot(UEs,throughput(12,:),'k');
hold on;
plot(UEs,throughput(15,:),'g');

UEs = [900,3000,6000,9000,12000,15000,18000,21000,24000,27000,30000,33000,36000,39000,42000,45000,48000];
plot(UEs,throughput(18,1:17),'d');
hold on;
plot(UEs,throughput(21,1:17),'o');
hold on;
plot(UEs,throughput(24,1:17),'x');
hold on;
plot(UEs,throughput(27,1:17),'s');
hold on;
plot(UEs,throughput(30,1:17),'^');
hold on;
xlabel('N');
ylabel('throughput(packets/slot)');
%ylim([0,5.5])
legend({'ana 1/\lambda = 120min','ana 1/\lambda = 60min','ana 1/\lambda = 30min','ana 1/\lambda = 12min','ana 1/\lambda = 5min','sim 1/\lambda = 120min','sim 1/\lambda = 60min','sim 1/\lambda = 30min','sim 1/\lambda = 12min','sim 1/\lambda = 5min'},'Location','northwest');
%{
xlabel('N');
ylabel('throughput_111_101010(packets/slot)');
legend({'sim inter-arrival time = 3min','ana inter-arrival time =
3min'},'Location','northwest');
%}
set(findall(gca, 'Type', 'Line'),'LineWidth',2);
