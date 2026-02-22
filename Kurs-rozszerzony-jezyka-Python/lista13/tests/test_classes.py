from data_access import *
import unittest
import sys
import os
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), "..")))


class TestFriendsDB(unittest.TestCase):
    def setUp(self):
        with Session(engine) as session:
            session.query(Friend).delete()
            session.commit()

    def tearDown(self):
        with Session(engine) as session:
            session.query(Friend).delete()
            session.commit()

    def test_add_friend(self):
        db_add_friend("Name", "email1@gmail.com", "123456789")
        with Session(engine) as session:
            friend = session.query(Friend).first()
            self.assertIsNotNone(friend)
            self.assertEqual(friend.name, "Name")

    def test_update_friend(self):
        db_add_friend("Name", "email1@gmail.com", "123456789")
        with Session(engine) as session:
            friend_id = session.query(Friend).first().id
        db_update_friend(
            friend_id,
            "Updated name",
            "updatedemail@gmail.com",
            "987654321")
        with Session(engine) as session:
            friend = session.get(Friend, friend_id)
            self.assertEqual(friend.name, "Updated name")
            self.assertEqual(friend.email, "updatedemail@gmail.com")
            self.assertEqual(friend.phone_number, "987654321")

    def test_delete_friend(self):
        db_add_friend("Name", "email1@gmail.com", "123456789")
        with Session(engine) as session:
            friend_id = session.query(Friend).first().id
        db_delete_friend(friend_id)
        with Session(engine) as session:
            friend = session.get(Friend, friend_id)
            self.assertIsNone(friend)

    def test_delete_friend_requires_login(self):
        db_add_friend("A", "a@a.pl", "123")
        with Session(engine) as session:
            friend_id = session.query(Friend).first().id

        with self.assertRaises(PermissionError):
            db_delete_friend(friend_id)
    
    def test_delete_friend_after_login(self):
        login("admin", "admin123")

        db_add_friend("A", "a@a.pl", "123")
        with Session(engine) as session:
            friend_id = session.query(Friend).first().id

        db_delete_friend(friend_id)

        with Session(engine) as session:
            self.assertIsNone(session.get(Friend, friend_id))

        logout()

    def test_logout_blocks_access(self):
        login("admin", "admin123")
        logout()

        with self.assertRaises(PermissionError):
            db_delete_friend(1)


