<?php
$koneksi = mysqli_connect("localhost", "root", "", "prakt6");

$sql = mysqli_query($koneksi, "SELECT kemiringan FROM piranti ORDER BY id DESC LIMIT 1");
$data = mysqli_fetch_array($sql);
$nilai = $data["kemiringan"];

echo $nilai;