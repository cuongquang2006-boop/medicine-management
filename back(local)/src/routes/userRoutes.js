const express = require("express");
const router = express.Router();

const
{
    getAllUsers,
    createUser,
    updateUser,
    deleteUser,
    loginUser
} = require("../controllers/userController");

router.get("/", getAllUsers);
router.post("/", createUser);
router.put("/:id", updateUser);
router.delete("/:id", deleteUser);
router.post("/login", loginUser);


module.exports = router;
