from sqlalchemy.orm import Session
from models.models import MQTTTopic, SessionLocal

def get_db():
    db = SessionLocal()
    try:
        yield db
    finally:
        db.close()

def get_mqtt_topics(db: Session):
    return db.query(MQTTTopic).all()
