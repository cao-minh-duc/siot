from sqlalchemy import Column, Integer, String, Float, DateTime, create_engine, Index
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import sessionmaker, relationship
from datetime import datetime

DATABASE_URL = "sqlite:///./data/app.db"

Base = declarative_base()

class MQTTTopic(Base):
    __tablename__ = "mqtt_topics"
    id = Column(Integer, primary_key=True, index=True)
    topic = Column(String, unique=True, index=True)


#Gateways        
class Gateway(Base):
    __tablename__ = "gateways"
    id = Column(Integer, primary_key=True, index=True)
    uuid = Column(String, unique=True, index=True)
    type = Column(String, nullable=False) # ("cloud", "edge", "service", "controller")
    status = Column(String, nullable=False)
    name = Column(String, nullable=False)
    created_at = Column(DateTime, default=datetime.utcnow)
    updated_at = Column(DateTime, default=datetime.utcnow, onupdate=datetime.utcnow)

class GatewayFollower(Base):
    __tablename__ = "gateway_followers"
    id = Column(Integer, primary_key=True, index=True)
    gateway_uuid = Column(String, index=True)
    follower_type = Column(String)
    follower_uuid = Column(String)

    # Define the relationship using foreign() to specify the non-enforced foreign key
    gateway = relationship("Gateway",
                           backref="followers",
                           primaryjoin="Gateway.uuid == foreign(GatewayFollower.gateway_uuid)")

class GatewayFollowing(Base):
    __tablename__ = "gateway_followings"
    id = Column(Integer, primary_key=True, index=True)
    gateway_uuid = Column(String, index=True)
    following_type = Column(String)
    following_uuid = Column(String)

    # Define the relationship using foreign() to specify the non-enforced foreign key
    gateway = relationship("Gateway",
                           backref="followings",
                           primaryjoin="Gateway.uuid == foreign(GatewayFollowing.gateway_uuid)")


# Devices
# Update the Controller class to include a gateway_uuid
class Controller(Base):
    __tablename__ = "controllers"
    id = Column(Integer, primary_key=True, index=True)
    uuid = Column(String, unique=True, index=True)
    type = Column(String, nullable=False)  # Controller type (e.g., "main", "secondary")
    status = Column(String, nullable=False)  # Controller status (e.g., "active", "inactive")
    name = Column(String, nullable=False)
    created_at = Column(DateTime, default=datetime.utcnow)
    updated_at = Column(DateTime, default=datetime.utcnow, onupdate=datetime.utcnow)
    
class Sensor(Base):
    __tablename__ = "sensors"
    id = Column(Integer, primary_key=True, index=True)
    uuid = Column(String, unique=True, index=True)
    controller_uuid = Column(String, index=True)  # Controller UUID
    type = Column(String, nullable=False)  # Sensor type (e.g., temperature, humidity, fire)
    status = Column(String, nullable=False)  # Sensor status (e.g., enable, disable)
    name = Column(String, nullable=False)
    created_at = Column(DateTime, default=datetime.utcnow)
    updated_at = Column(DateTime, default=datetime.utcnow, onupdate=datetime.utcnow)
    
    controller = relationship("Controller",
                           backref="sensors",
                           primaryjoin="Controller.uuid == foreign(Sensor.controller_uuid)")
    
class Actuator(Base):
    __tablename__ = "actuators"
    id = Column(Integer, primary_key=True, index=True)
    uuid = Column(String, unique=True, index=True)
    controller_uuid = Column(String, index=True)  # Controller UUID
    type = Column(String, nullable=False)  # Actuator type (e.g., motor, light, relay)
    name = Column(String, nullable=False)
    created_at = Column(DateTime, default=datetime.utcnow)
    updated_at = Column(DateTime, default=datetime.utcnow, onupdate=datetime.utcnow)
    
    controller = relationship("Controller",
                           backref="actuators",
                           primaryjoin="Controller.uuid == foreign(Actuator.controller_uuid)")
    
    
# Collections
class ControllerCollectionActivity(Base):
    __tablename__ = "controller_collection_activities"
    id = Column(Integer, primary_key=True, index=True)
    activity_uuid = Column(String, nullable=False, index=True)  # UUID of the specific activity record
    controller_uuid = Column(String, nullable=False, index=True)  # UUID of the associated controller
    end_device_uuid = Column(String, nullable=False, index=True)  # UUID of the sensor or actuator
    created_at = Column(DateTime, default=datetime.utcnow)
    
    controller = relationship("Controller",
                           backref="activities",
                           primaryjoin="Controller.uuid == foreign(ControllerCollectionActivity.controller_uuid)")
    
    # Indexes for performance optimization
    __table_args__ = (
        Index('idx_controller_activity_created_at', 'controller_uuid', 'created_at'),
    )
    

class SensorCollectionActivity(Base):
    __tablename__ = "sensor_collection_activities"
    id = Column(Integer, primary_key=True, index=True)
    sensor_uuid = Column(String, index=True, nullable=False)  # Indexed field instead of a foreign key
    activity_type = Column(String, nullable=False)  # Type of activity (e.g., temperature, humidity, fire)
    activity_uuid = Column(String, nullable=False)  # UUID of the specific activity record
    created_at = Column(DateTime, default=datetime.utcnow)

    sensor = relationship("Sensor",
                           backref="activities",
                           primaryjoin="Sensor.uuid == foreign(SensorCollectionActivity.sensor_uuid)")
    
    # Indexes for performance optimization
    __table_args__ = (
        Index('idx_sensor_activity_created_at', 'sensor_uuid', 'created_at'),
    )

        
class ActuatorCollectionActivity(Base):
    __tablename__ = "actuator_collection_activities"
    id = Column(Integer, primary_key=True, index=True)
    actuator_uuid = Column(String, index=True, nullable=False)  # Indexed field instead of a foreign key
    activity_type = Column(String, nullable=False)  # Type of activity (e.g., relay, motor)
    activity_uuid = Column(String, nullable=False)  # UUID of the specific activity record
    created_at = Column(DateTime, default=datetime.utcnow)
    
    
    actuator = relationship("Actuator",
                           backref="activities",
                           primaryjoin="Actuator.uuid == foreign(ActuatorCollectionActivity.actuator_uuid)")
    
    # Indexes for performance optimization
    __table_args__ = (
        Index('idx_activity_created_at', 'actuator_uuid', 'created_at'),
    )


# Activities
class GatewayFollowActivity(Base):
    __tablename__ = "gateway_follow_activities"
    id = Column(Integer, primary_key=True, index=True)
    uuid = Column(String, unique=True, index=True)
    gateway_uuid = Column(String, index=True)  # Reference to the Gateway UUID
    type = Column(String, nullable=False)  # Activity type (e.g., "follow", "unfollow")
    created_at = Column(DateTime, default=datetime.utcnow)

    gateway = relationship("Gateway",
                           backref="follow_activities",
                           primaryjoin="Gateway.uuid == foreign(GatewayFollowActivity.gateway_uuid)")
    
    __table_args__ = (
        Index('idx_gateway_activity_created_at', 'gateway_uuid', 'created_at'),
    )
    
class TemperatureActivity(Base):
    __tablename__ = "temperature_activities"
    id = Column(Integer, primary_key=True, index=True)
    uuid = Column(String, unique=True, index=True)
    sensor_uuid = Column(String, index=True)  # No foreign key constraint, just a regular column
    value = Column(Float, nullable=False)
    created_at = Column(DateTime, default=datetime.utcnow)

    sensor = relationship("Sensor",
                           backref="temperature_activities",
                           primaryjoin="Sensor.uuid == foreign(TemperatureActivity.sensor_uuid)")
    
    # Indexes for performance optimization
    __table_args__ = (
        Index('idx_fire_activity_created_at', 'sensor_uuid', 'created_at'),
    )


class HumidityActivity(Base):
    __tablename__ = "humidity_activities"
    id = Column(Integer, primary_key=True, index=True)
    uuid = Column(String, unique=True, index=True)
    sensor_uuid = Column(String, index=True)  # No foreign key constraint, just a regular column
    value = Column(Float, nullable=False)
    created_at = Column(DateTime, default=datetime.utcnow)


    sensor = relationship("Sensor",
                           backref="humidity_activities",
                           primaryjoin="Sensor.uuid == foreign(HumidityActivity.sensor_uuid)")
    
    # Indexes for performance optimization
    __table_args__ = (
        Index('idx_humidity_activity_created_at', 'sensor_uuid', 'created_at'),
    )


class FireActivity(Base):
    __tablename__ = "fire_activities"
    id = Column(Integer, primary_key=True, index=True)
    uuid = Column(String, unique=True, index=True)
    sensor_uuid = Column(String, index=True)  # No foreign key constraint, just a regular column
    status = Column(String, nullable=False)  # Status indicating if fire is detected (e.g., "detected", "not_detected")
    created_at = Column(DateTime, default=datetime.utcnow)

    sensor = relationship("Sensor",
                           backref="fire_activities",
                           primaryjoin="Sensor.uuid == foreign(FireActivity.sensor_uuid)")
    
    # Indexes for performance optimization
    __table_args__ = (
        Index('idx_sensor_activity_created_at', 'sensor_uuid', 'created_at'),
    )


class RelayActivity(Base):
    __tablename__ = "relay_activities"
    id = Column(Integer, primary_key=True, index=True)
    uuid = Column(String, unique=True, index=True)
    actuator_uuid = Column(String, index=True)  # No foreign key constraint, just a regular column
    status = Column(String, nullable=False)  # Status indicating relay state (e.g., "on", "off")
    created_at = Column(DateTime, default=datetime.utcnow)

    actuator = relationship("Actuator",
                           backref="relay_activities",
                           primaryjoin="Actuator.uuid == foreign(RelayActivity.actuator_uuid)")
    
    # Indexes for performance optimization
    __table_args__ = (
        Index('idx_actuator_activity_created_at', 'actuator_uuid', 'created_at'),
    )

    
# Database engine
engine = create_engine(DATABASE_URL)
SessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=engine)

# Create tables
Base.metadata.create_all(bind=engine)
