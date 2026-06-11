const express = require("express");
const router = express.Router();

const
{
    getDashboardStats,
    getRecentPrescriptions,
    getLowStockMedicines
} = require("../controllers/dashboardController");

router.get("/stats", getDashboardStats);
router.get("/recent-prescriptions", getRecentPrescriptions);
router.get("/low-stock", getLowStockMedicines);

module.exports = router;