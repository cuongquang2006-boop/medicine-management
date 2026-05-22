const express = require("express");
const routes = express.Router();

const {
    getAllMedicines,
    createMedicine,
    updateMedicine,
    deleteMedicine
} = require("../controllers/medicineController");


routes.get("/",getAllMedicines);
routes.post("/",createMedicine);
routes.put("/:id",updateMedicine);
routes.delete("/:id",deleteMedicine);

module.exports = routes;