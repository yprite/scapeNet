create table ip_data(
pid int(10) not null auto_increment primary key,
ip varchar(20),
mac varchar(20),
up_traffic_cur varchar(10),
down_traffic_cur varchar(10),
up_traffic_limit varchar(10),
down_traffic_limit varchar(10),
isStatus varchar(2));
