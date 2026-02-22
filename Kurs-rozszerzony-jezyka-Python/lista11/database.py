from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker
from models import Base

DB_NAME = "library.db"

engine = create_engine(f"sqlite:///{DB_NAME}")
Session = sessionmaker(bind=engine)

def init_db():
    Base.metadata.create_all(engine)
