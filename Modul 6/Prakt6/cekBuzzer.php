<?php
$koneksi = mysqli_connect("localhost", "root", "", "prakt6");

$sql = mysqli_query($koneksi, "SELECT indikator_buzzer FROM piranti ORDER BY id DESC LIMIT 1");
$data = mysqli_fetch_array($sql);
$nilai = $data["indikator_buzzer"];

echo $nilai;