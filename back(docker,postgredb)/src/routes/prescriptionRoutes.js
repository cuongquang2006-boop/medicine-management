const express = require("express");
const router = express.Router();

const {
    getAllPrescriptions,
    createPrescription
} = require("../controllers/prescriptionController");

router.get("/", getAllPrescriptions);
router.post("/", createPrescription);

module.exports = router;