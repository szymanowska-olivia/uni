from __future__ import annotations
from sqlalchemy.orm import DeclarativeBase, relationship, Mapped, mapped_column, validates
from sqlalchemy import Integer, String, ForeignKey, Date
from typing import List
from datetime import date

class Base(DeclarativeBase):
    pass


class Book(Base):
    __tablename__ = "books"

    id: Mapped[int] = mapped_column(primary_key=True)
    title: Mapped[str]
    author: Mapped[str]
    year: Mapped[int]

    loans: Mapped[List["Loan"]] = relationship(back_populates="book")

    @validates("year")
    def validate_year(self, key, year):
        if year < 0:
            raise ValueError("Year must be positive")
        return year


class Friend(Base):
    __tablename__ = "friends"

    id: Mapped[int] = mapped_column(primary_key=True)
    name: Mapped[str]
    email: Mapped[str]
    phone: Mapped[str]

    loans: Mapped[List["Loan"]] = relationship(back_populates="friend")

    @validates("email")
    def validate_email(self, key, email):
        if "@" not in email:
            raise ValueError("Invalid email")
        return email


class Loan(Base):
    __tablename__ = "loans"

    id: Mapped[int] = mapped_column(primary_key=True)
    book_id: Mapped[int] = mapped_column(ForeignKey("books.id"))
    friend_id: Mapped[int] = mapped_column(ForeignKey("friends.id"))
    loan_date: Mapped[date] = mapped_column(Date)
    return_date: Mapped[date | None] = mapped_column(Date, nullable=True)

    book: Mapped["Book"] = relationship(back_populates="loans")
    friend: Mapped["Friend"] = relationship(back_populates="loans")

    @validates("return_date")
    def validate_return_date(self, key, value):
        if value and value < self.loan_date:
            raise ValueError("Return date cannot be earlier than loan date")
        return value
