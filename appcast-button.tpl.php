<?php
/**
* This file is part of the Appcast module for Drupal
* Copyright (c) 2009 Sebastiaan Deckers
* License: GNU General Public License version 3 or later
*
* @file appcast-button.tpl.php
*
* Theme implementation to display a download button block.
*
* Available module variables:
* - $css: Class name for the download button. Customized in the settings.
* - $feed: URL of the appcast Atom 1.0 document.
* - $filename: Filename component of the enclosure URL.
* - $href: Link address for the download button. Customized in the settings.
* - $mirror: Flag (0 or 1) whether or not the enclosure is being downloaded locally.
* - $name: Name of the software application. Customized in the settings.
* - $path: Location of the mirrored enclosure on disk. Customized in the settings.
* - $size: Number of bytes for the enclosure as reported by the appcast. May differ from the actual file.
* - $sizeKB: Number of kilobytes (1024) converted from $size with one digit precision.
* - $sizeMB: Number of megabytes (1024^2) converted from $size with one digit precision.
* - $sizeGB: Number of gigabytes (1024^3) converted from $size with one digit precision.
* - $style: Which type of block is being shown. Possible values: "", "beta", "narrow", "narrow beta"
* - $timestamp: Release time of the enclosure. Format is an ISO8601/RFC3339 string.
* - $track: Track the enclosure was released on. Customized in the settings.
* - $url: Download link to the enclosure from the appcast feed. This is not the locally mirrored file.
* - $version: Enclosure version number.
*/
?>
<h1><? echo $name . ' ' . $version ?></h1>
<a href="<? echo $href . $filename ?>" class="<? echo $css . ' ' . $style ?>">
<? echo $filename ?> (<? echo $sizeKB ?> kilobytes)
</a>
